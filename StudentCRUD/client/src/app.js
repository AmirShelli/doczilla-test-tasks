document.addEventListener("DOMContentLoaded", () => {
    getAllStudents();
  

    const addForm = document.getElementById("addStudentForm");
    addForm.addEventListener("submit", createStudent);
  

    const deleteForm = document.getElementById("deleteStudentForm");
    deleteForm.addEventListener("submit", deleteStudentById);
  });

function getAllStudents() {
  const table = document
    .getElementById("studentsTable")
    .getElementsByTagName("tbody")[0];
    table.innerHTML = "";

  fetch("http://localhost:8080/api/students")
    .then((response) => response.json())
    .then((data) => {
      data.forEach((student) => {
        const row = table.insertRow();
        const cellId = row.insertCell(0);
        const cellFirstName = row.insertCell(1);
        const cellLastName = row.insertCell(2);
        const cellMiddleName = row.insertCell(3);
        const cellBirthDate = row.insertCell(4);
        const cellGroup = row.insertCell(5);

        cellId.appendChild(document.createTextNode(student.id));
        cellFirstName.appendChild(document.createTextNode(student.firstName));
        cellLastName.appendChild(document.createTextNode(student.lastName));
        cellMiddleName.appendChild(document.createTextNode(student.middleName));
        cellBirthDate.appendChild(document.createTextNode(student.birthDate));
        cellGroup.appendChild(document.createTextNode(student.studentGroup));
      });
    })
    .catch((error) => console.error("Error fetching students: ", error));
}

function createStudent() {
  event.preventDefault();

  const form = document.getElementById("addStudentForm");
  const formData = new FormData(form);
  const formDataObject = {};

  for(let [name, value] of formData) {
    formDataObject[name] = value;
  }

  fetch("http://localhost:8080/api/students", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(formDataObject),
  })
  .catch((error) => console.error("Error creating student: ", error));
}

function deleteStudentById(event) {
    event.preventDefault();
  
    const studentId = document.getElementById("id").value;
  
    fetch(`http://localhost:8080/api/students/${studentId}`, {
      method: "DELETE",
    })
      .then((response) => {
        if (response.ok) {
          console.log(`Student with ID ${studentId} deleted.`);
          getAllStudents();
        }
      })
      .catch((error) => console.error("Error deleting student: ", error));
  }