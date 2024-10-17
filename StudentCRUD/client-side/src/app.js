const API_URL = "http://localhost:8080/api/students";

document.addEventListener("DOMContentLoaded", () => {
  getAllStudents();

  const refreshBtn = document.getElementById("refreshButton");
  refreshBtn.addEventListener("click", getAllStudents);

  const addForm = document.getElementById("insertStudentForm");
  addForm.addEventListener("submit", createStudent);

  const deleteForm = document.getElementById("deleteStudentForm");
  deleteForm.addEventListener("submit", deleteStudentById);
});

async function getAllStudents() {
  const table = document
    .getElementById("studentsTable")
    .getElementsByTagName("tbody")[0];
  table.innerHTML = "";

  try {
    const response = await fetch(API_URL);
    const data = await response.json();
    console.log(JSON.stringify(data));
    data.forEach((student) => {
      const row = table.insertRow();
      row.insertCell(0).appendChild(document.createTextNode(student.id));
      row.insertCell(1).appendChild(document.createTextNode(student.firstName));
      row.insertCell(2).appendChild(document.createTextNode(student.lastName));
      row
        .insertCell(3)
        .appendChild(document.createTextNode(student.middleName));
      row.insertCell(4).appendChild(document.createTextNode(student.birthDate));
      row
        .insertCell(5)
        .appendChild(document.createTextNode(student.studentGroup));
    });
  } catch (error) {
    console.error("Error fetching students: ", error);
  }
}

async function createStudent(event) {
  event.preventDefault();

  const form = document.getElementById("insertStudentForm");
  const formData = new FormData(form);
  const formDataObject = Object.fromEntries(formData);

  try {
    await fetch(API_URL, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(formDataObject),
    });
    if (response.ok) {
      console.log(`Student created.`);
      getAllStudents();
    }
  } catch (error) {
    console.error("Error creating student: ", error);
  }
}

async function deleteStudentById(event) {
  event.preventDefault();

  const studentId = document.getElementById("id").value;

  try {
    const response = await fetch(API_URL + `/${studentId}`, {
      method: "DELETE",
    });
    if (response.ok) {
      console.log(`Student with ID ${studentId} deleted.`);
      getAllStudents();
    }
  } catch (error) {
    console.error("Error deleting student: ", error);
  }
}
