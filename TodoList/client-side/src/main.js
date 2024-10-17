import { initializeDatePicker } from './modules/dateFilter.js';
import { fetchTasks, displayTasks, applyUncompletedFilter } from './modules/taskManager.js';
import { handleEvents } from './modules/uiHandler.js';

$(document).ready(function () {
    initializeDatePicker();

    fetchTasks().then(() => {
        applyUncompletedFilter();
        displayTasks();
    });

    handleEvents();
});
