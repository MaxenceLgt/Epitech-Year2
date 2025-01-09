FROM jenkins/jenkins:latest-jdk17

COPY my_marvin.yml /usr/share/jenkins/ref/casc_config/my_marvin.yml
COPY job_dsl.groovy /usr/share/jenkins/init.groovy.d/job_dsl.groovy

RUN jenkins-plugin-cli --plugins "configuration-as-code:latest job-dsl:latest cloudbees-folder:latest credentials:latest github:latest instance-identity:latest script-security:latest structs:latest role-strategy:latest ws-cleanup:latest"