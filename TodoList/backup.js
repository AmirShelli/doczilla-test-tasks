
$(document).ready(function () {
    let allTasks = [];
    let tasks = [];

    let dateRange = { start: null, end: null };


    $("#date-range-picker").datepicker({
        dateFormat: "yy-mm-dd",
        onSelect: function (dateText) {
            const selectedDate = stripTime(new Date(dateText));

            if (!dateRange.start || dateRange.end) {
                setDateRange(selectedDate);
            } else if (!dateRange.end) {
                if (selectedDate >= dateRange.start) {
                    setDateRange(dateRange.start, selectedDate);
                } else {
                    setDateRange(selectedDate);
                }
            }
        }
    });

    function stripTime(date) {
        return new Date(date.getFullYear(), date.getMonth(), date.getDate());
    }

    function filterByDateRange() {
        if (dateRange.start && dateRange.end) {
            const startDate = stripTime(dateRange.start);
            const endDate = stripTime(dateRange.end);
            const filteredTasks = tasks.filter(task => {
                const taskDate = stripTime(new Date(task.date));
                return (taskDate >= startDate) && (taskDate <= endDate);
            });

            displayTasks(filteredTasks);
        } else if (dateRange.start && !dateRange.end) {
            const startDate = stripTime(dateRange.start);
            const filteredTasks = tasks.filter(task => {
                const taskDate = stripTime(new Date(task.date));
                return taskDate.getTime() === startDate.getTime(); // stripTime() resets to 00:00:00
            });

            displayTasks(filteredTasks);
        }
        else {
            displayTasks(tasks);
        }
    }


    function fetchTasks() {
        $.ajax({
            url: 'http://localhost:3000/api/todos',
            method: 'GET',
            success: function (data) {
                allTasks = data;
                tasks = [...allTasks];
                applyUncompletedFilter();
                displayTasks(tasks);
            },
            error: function (err) {
                console.error("Error fetching tasks:", err);
            }
        });
    }

    function displayTasks(filteredTasks) {
        const container = $('#tasks');
        container.empty();

        const list = $('<ul class="list-group"></ul>');

        filteredTasks.forEach(function (task) {
            const listItem = $(`
    <li class="list-group-item task-item" data-id="${task.id}">
        <strong>${task.name}</strong><br>
        ${task.shortDesc}<br>
        <small>${new Date(task.date).toLocaleDateString()}</small><br>
        <span>Status: ${task.status ? "Completed" : "Uncompleted"}</span>
    </li>
`);
            list.append(listItem);
        });

        container.append(list);
    }


    fetchTasks();


    function applyUncompletedFilter() {
        if ($('#show-uncompleted').is(':checked')) {
            tasks = allTasks.filter(task => !task.status);
        } else {
            tasks = [...allTasks];
        }
    }

    $('#search-task').on('input', function () {
        const query = $(this).val().toLowerCase();
        let filteredTasks = tasks.filter(task => task.name.toLowerCase().includes(query));
        displayTasks(filteredTasks);
    });

    function setDateRange(start, end = null) {
        dateRange.start = stripTime(start);
        dateRange.end = end ? stripTime(end) : null;
        filterByDateRange();
    }

    $('#today-btn').on('click', function () {
        const today = new Date();
        setDateRange(today);
    });

    $('#week-btn').on('click', function () {
        const today = new Date();
        const firstDayOfWeek = stripTime(new Date(today.setDate(today.getDate() - today.getDay())));
        const lastDayOfWeek = new Date(firstDayOfWeek);
        lastDayOfWeek.setDate(firstDayOfWeek.getDate() + 6);
        setDateRange(firstDayOfWeek, lastDayOfWeek);
    });

    $('#sort-by').on('change', function () {
        const sortOrder = $(this).val();
        sortTasks(sortOrder);
    });

    function sortTasks(order) {
        if (order === "asc") {
            tasks.sort((a, b) => new Date(a.date) - new Date(b.date));
        } else if (order === "desc") {
            tasks.sort((a, b) => new Date(b.date) - new Date(a.date));
        }
        displayTasks(tasks);
    }

    $('#show-uncompleted').on('change', function () {
        applyUncompletedFilter();
        displayTasks(tasks);
    });

    $(document).on('click', '.task-item', function () {
        const taskId = $(this).data('id');
        const task = allTasks.find(t => t.id === taskId);

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
});
