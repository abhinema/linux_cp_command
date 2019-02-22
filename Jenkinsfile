pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'echo "Hello World"'
                sh '''
                echo "Multiline shell steps works too"
                ls -lah
                '''
                sh "mkdir -p build"
                dir ('build') {
                    echo "Build folder created"
                    sh 'echo "artifact file" > generatedFile.txt'
                    
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
    }
}

