document.getElementById('schedulingAlgorithm').addEventListener('change', function() {
    const algorithm = this.value;
    const timeQuantumLabel = document.getElementById('timeQuantumLabel');
    const timeQuantumInput = document.getElementById('timeQuantum');

    if (algorithm === 'rr') {
        timeQuantumLabel.style.display = 'inline';
        timeQuantumInput.style.display = 'inline';
    } else {
        timeQuantumLabel.style.display = 'none';
        timeQuantumInput.style.display = 'none';
    }
});

function generateProcessInputs() {
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputsDiv = document.getElementById('processInputs');
    processInputsDiv.innerHTML = '';

    for (let i = 0; i < numProcesses; i++) {
        processInputsDiv.innerHTML += `
            <div>
                <label>Process ${i + 1} Arrival Time:</label>
                <input type="number" id="arrivalTime${i}" min="0">
                <label>Burst Time:</label>
                <input type="number" id="burstTime${i}" min="1">
            </div>
        `;
    }
}

function generateRandomValues() {
    const numProcesses = document.getElementById('numProcesses').value;
    const processInputsDiv = document.getElementById('processInputs');
    processInputsDiv.innerHTML = '';

    for (let i = 0; i < numProcesses; i++) {
        const arrivalTime = Math.floor(Math.random() * 10); // Random arrival time between 0 to 9
        const burstTime = Math.floor(Math.random() * 10) + 1; // Random burst time between 1 to 10

        processInputsDiv.innerHTML += `
            <div>
                <label>Process ${i + 1} Arrival Time:</label>
                <input type="number" id="arrivalTime${i}" min="0" value="${arrivalTime}">
                <label>Burst Time:</label>
                <input type="number" id="burstTime${i}" min="1" value="${burstTime}">
            </div>
        `;
    }
}

function runSchedulingAlgorithm() {
    const numProcesses = document.getElementById('numProcesses').value;
    const algorithm = document.getElementById('schedulingAlgorithm').value;
    const timeQuantum = parseInt(document.getElementById('timeQuantum').value);

    let processes = [];
    for (let i = 0; i < numProcesses; i++) {
        processes.push({
            id: i + 1,
            arrivalTime: parseInt(document.getElementById(`arrivalTime${i}`).value),
            burstTime: parseInt(document.getElementById(`burstTime${i}`).value),
            originalBurstTime: parseInt(document.getElementById(`burstTime${i}`).value), // Storing original burst time for calculation
            completionTime: 0,
            turnAroundTime: 0,
            waitingTime: 0,
            color: getRandomColor() // Assigning a random color to each process
        });
    }

    let ganttChart = [];

    switch (algorithm) {
        case 'fcfs':
            fcfs(processes, ganttChart);
            break;
        case 'sjf':
            sjf(processes, ganttChart);
            break;
        case 'rr':
            rr(processes, ganttChart, timeQuantum);
            break;
        case 'sjrf':
            sjrf(processes, ganttChart);
            break;
    }

    displayResults(processes, ganttChart);
    displayGanttChart(ganttChart);
}

function displayResults(processes, ganttChart) {
    const resultsTable = document.getElementById('resultsTable').getElementsByTagName('tbody')[0];
    resultsTable.innerHTML = '';

    let totalTurnAroundTime = 0;
    let totalWaitingTime = 0;

    processes.forEach(process => {
        const row = resultsTable.insertRow();
        row.insertCell(0).innerText = process.id;
        row.insertCell(1).innerText = process.arrivalTime;
        row.insertCell(2).innerText = process.originalBurstTime;
        row.insertCell(3).innerText = process.completionTime;
        row.insertCell(4).innerText = process.turnAroundTime;
        row.insertCell(5).innerText = process.waitingTime;

        totalTurnAroundTime += process.turnAroundTime;
        totalWaitingTime += process.waitingTime;
    });

    const averageTurnAroundTime = totalTurnAroundTime / processes.length;
    const averageWaitingTime = totalWaitingTime / processes.length;

    document.getElementById('averageTimes').innerText = `
        Average Turn Around Time: ${averageTurnAroundTime.toFixed(2)} 
        Average Waiting Time: ${averageWaitingTime.toFixed(2)}
    `;
}

function displayGanttChart(ganttChart) {
    const ganttChartContainer = document.getElementById('ganttChartContainer');
    ganttChartContainer.innerHTML = '';

    const totalExecutionTime = ganttChart[ganttChart.length - 1].endTime;

    ganttChart.forEach(entry => {
        const processDiv = document.createElement('div');
        processDiv.className = 'gantt-bar';
        processDiv.style.backgroundColor = entry.color;
        processDiv.style.width = `${(entry.endTime - entry.startTime) / totalExecutionTime * 100}%`;
        processDiv.innerHTML = `<span>P${entry.processId}</span>`;
        ganttChartContainer.appendChild(processDiv);
    });
}

function fcfs(processes, ganttChart) {
    processes.sort((a, b) => a.arrivalTime - b.arrivalTime);
    let currentTime = 0;

    processes.forEach(process => {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        ganttChart.push({ processId: process.id, startTime: currentTime, endTime: currentTime + process.burstTime, color: process.color });
        process.completionTime = currentTime + process.burstTime;
        process.turnAroundTime = process.completionTime - process.arrivalTime;
        process.waitingTime = process.turnAroundTime - process.burstTime;
        currentTime = process.completionTime;
    });
}

function sjf(processes, ganttChart) {
    processes.sort((a, b) => a.arrivalTime - b.arrivalTime);
    let currentTime = 0;
    let remainingProcesses = [...processes];

    while (remainingProcesses.length > 0) {
        let availableProcesses = remainingProcesses.filter(p => p.arrivalTime <= currentTime);
        if (availableProcesses.length > 0) {
            availableProcesses.sort((a, b) => a.burstTime - b.burstTime);
            let process = availableProcesses[0];
            ganttChart.push({ processId: process.id, startTime: currentTime, endTime: currentTime + process.burstTime, color: process.color });
            currentTime += process.burstTime;
            process.completionTime = currentTime;
            process.turnAroundTime = process.completionTime - process.arrivalTime;
            process.waitingTime = process.turnAroundTime - process.originalBurstTime;
            remainingProcesses = remainingProcesses.filter(p => p.id !== process.id);
        } else {
            currentTime++;
        }
    }
}

function rr(processes, ganttChart, timeQuantum) {
    let currentTime = 0;
    let queue = [];
    processes.sort((a, b) => a.arrivalTime - b.arrivalTime);

    let remainingProcesses = [...processes];
    while (remainingProcesses.length > 0 || queue.length > 0) {
        while (remainingProcesses.length > 0 && remainingProcesses[0].arrivalTime <= currentTime) {
            queue.push(remainingProcesses.shift());
        }

        if (queue.length > 0) {
            let process = queue.shift();
            let executionTime = Math.min(process.burstTime, timeQuantum);
            ganttChart.push({ processId: process.id, startTime: currentTime, endTime: currentTime + executionTime, color: process.color });
            process.burstTime -= executionTime;
            currentTime += executionTime;

            if (process.burstTime > 0) {
                while (remainingProcesses.length > 0 && remainingProcesses[0].arrivalTime <= currentTime) {
                    queue.push(remainingProcesses.shift());
                }
                queue.push(process);
            } else {
                process.completionTime = currentTime;
                process.turnAroundTime = process.completionTime - process.arrivalTime;
                process.waitingTime = process.turnAroundTime - process.originalBurstTime;
            }
        } else {
            currentTime++;
        }
    }
}

function sjrf(processes, ganttChart) {
    processes.sort((a, b) => a.arrivalTime - b.arrivalTime);
    let currentTime = 0;
    let remainingProcesses = [...processes];

    while (remainingProcesses.length > 0) {
        let availableProcesses = remainingProcesses.filter(p => p.arrivalTime <= currentTime);
        if (availableProcesses.length > 0) {
            availableProcesses.sort((a, b) => a.burstTime - b.burstTime);
            let process = availableProcesses[0];
            ganttChart.push({ processId: process.id, startTime: currentTime, endTime: currentTime + 1, color: process.color });
            currentTime++;
            process.burstTime--;

            if (process.burstTime === 0) {
                process.completionTime = currentTime;
                process.turnAroundTime = process.completionTime - process.arrivalTime;
                process.waitingTime = process.turnAroundTime - process.originalBurstTime;
                remainingProcesses = remainingProcesses.filter(p => p.id !== process.id);
            }
        } else {
            currentTime++;
        }
    }
}

// Function to generate a random HSL color
function getRandomColor() {
    return `hsl(${Math.random() * 360}, 100%, 75%)`;
}
