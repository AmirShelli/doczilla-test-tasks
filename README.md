# doczilla-test-tasks

To run the program enter the main directory
and execute the following line:

```
make run arg=<folderName>
```

# TASK 2

## Overview

StudentCRUD is a simple application that allows managing student records. It consists of a Java-based backend server, a PostgreSQL database, and a frontend served via NGINX written in Vanilla JavaScript.

## Prerequisites

- **Docker & Docker Compose**
  - [Install Docker](https://docs.docker.com/get-docker/)
  - [Install Docker Compose](https://docs.docker.com/compose/install/)

## Setup

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/StudentCRUD.git
cd StudentCRUD
```

### 2. Build and Run with Docker Compose

```bash
docker-compose up --build
```

* Access the Frontend: http://localhost
* Access the Backend API: http://localhost:8080/api/students
* PostgreSQL: Accessible on localhost:5432
