FROM gradle:latest AS build

WORKDIR /app

COPY build.gradle settings.gradle /app/

COPY gradle /app/gradle/

RUN gradle shadowJar --no-daemon

COPY src /app/src/

RUN gradle shadowJar --no-daemon

FROM openjdk:latest

WORKDIR /app

COPY --from=build /app/build/libs/studentcrud-server-1.0.jar /app/app.jar

EXPOSE 8080

ENTRYPOINT ["java", "-jar", "/app/app.jar"]
