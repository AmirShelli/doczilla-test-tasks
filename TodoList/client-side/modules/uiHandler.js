import { setDateRange, stripTime } from './dateFilter.js';
import { getTasks, displayTasks, applyUncompletedFilter, sortTasks } from './taskManager.js';

export function handleEvents() {
    $('#today-btn').on('click', function () {
        const today = new Date();
        setDateRange(today);
        $('#date-range-picker').datepicker('setDate', today);
        $('#date-range-picker').datepicker('refresh');
    });

    $('#week-btn').on('click', function () {
        const today = new Date();
        const firstDayOfWeek = stripTime(new Date(today.setDate(today.getDate() - today.getDay())));
        const lastDayOfWeek = new Date(firstDayOfWeek);
        lastDayOfWeek.setDate(firstDayOfWeek.getDate() + 6);
        setDateRange(firstDayOfWeek, lastDayOfWeek);
        $('#date-range-picker').datepicker('setDate', firstDayOfWeek);
        $('#date-range-picker').datepicker('refresh');
    });

    $('#search-task').on('input', function () {
        const query = $(this).val().toLowerCase();
        let filteredTasks = getTasks().filter(task => task.name.toLowerCase().includes(query));
        displayTasks(filteredTasks);
    });

    $('#sort-by').on('change', function () {
        const sortOrder = $(this).val();
        sortTasks(sortOrder);
    });

    $('#show-uncompleted').on('change', function () {
        applyUncompletedFilter();
        displayTasks();
    });

    $(document).on('click', '.task-item', function (e) {
        if ($(e.target).is('.status-toggle')) {
            return;
        }
        const taskId = $(this).data('id');
        const task = getTasks().find(t => t.id === taskId);
        if (task) {
            $('#myModal .modal-title').text(task.name);
            $('#myModal .modal-body').html(`
                <p><strong>Description:</strong> ${task.fullDesc || task.shortDesc}</p>
                <p><strong>Date:</strong> ${new Date(task.date).toLocaleDateString()}</p>
                <p><strong>Status:</strong> ${task.status ? "Completed" : "Uncompleted"}</p>
            `);
            $("#myModal").modal("show");
        } else {
            console.error(`Task with ID ${taskId} not found.`);
        }
    });

}
