import { stripTime, getDateRange, setFilterCallback } from './dateFilter.js';

let allTasks = [];
let tasks = [];

export async function fetchTasks() {
    try {
        const response = await $.ajax({
            url: 'http://localhost:3000/api/todos',
            method: 'GET'
        });
        allTasks = response;
        tasks = [...allTasks];
    } catch (err) {
        console.error("Error fetching tasks:", err);
    }
}

export function applyUncompletedFilter() {
    if ($('#show-uncompleted').is(':checked')) {
        tasks = allTasks.filter(task => !task.status);
    } else {
        tasks = [...allTasks];
    }
}

export function displayTasks(filteredTasks = null) {
    const container = $('#tasks');
    container.empty();

    const tasksToDisplay = filteredTasks ? filteredTasks : getFilteredTasks();

    if (tasksToDisplay.length === 0) {
        container.append('<p class="text-muted">No tasks found for the selected criteria.</p>');
        return;
    }

    const list = $('<ul class="list-group"></ul>');

    tasksToDisplay.forEach(function (task) {
        const statusIcon = task.status
        ? '<i class="fas fa-check-circle status-icon completed"></i>'
        : '<i class="fas fa-circle status-icon incomplete"></i>';

        const listItem = $(`
            <li class="list-group-item task-item" data-id="${task.id}" tabindex="0">
                <div class="d-flex justify-content-between align-items-center">
                    <div>
                        <strong>${task.name}</strong><br>
                        ${task.shortDesc}<br>
                        <small>${new Date(task.date).toLocaleDateString()}</small>
                    </div>
                    <div>
                        ${statusIcon}
                    </div>
                </div>
            </li>
        `);
        list.append(listItem);
    });

    container.append(list);
}

export function getFilteredTasks() {
    const { start, end } = getDateRange();
    if (start && end) {
        return tasks.filter(task => {
            const taskDate = stripTime(new Date(task.date));
            return (taskDate >= start) && (taskDate <= end);
        });
    } else if (start && !end) {
        return tasks.filter(task => {
            const taskDate = stripTime(new Date(task.date));
            return taskDate === start;
        });
    } else {
        return tasks;
    }
}

export function sortTasks(order) {
    if (order === "asc") {
        tasks.sort((a, b) => new Date(a.date) - new Date(b.date));
    } else if (order === "desc") {
        tasks.sort((a, b) => new Date(b.date) - new Date(a.date));
    }
    displayTasks();
}

export function getTasks() {
    return tasks;
}

setFilterCallback(displayTasks);
