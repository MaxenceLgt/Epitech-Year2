folder('/Tools') {
    description('Folder for miscellaneous tools.')
    displayName('Tools')
}
job('/Tools/clone-repository') {
    wrappers {
          preBuildCleanup {
            preBuildCleanup()
          }
        }
    displayName('clone-repository')
    parameters {
        stringParam("GIT_REPOSITORY_URL", null, "Git URL of the repository to clone")
    }
    steps {
        shell('git clone $GIT_REPOSITORY_URL')
    }
}
job('/Tools/SEED') {
    parameters {
        stringParam("GITHUB_NAME", null, "GitHub repository owner/repo_name (e.g.: \"EpitechIT31000/chocolatine\")")
        stringParam("DISPLAY_NAME", null, "Display name for the job")
    }
    steps {
        dsl {
            text('''
            freeStyleJob("$DISPLAY_NAME") {
                wrappers {
                    preBuildCleanup()
                }
                scm {
                    github("$GITHUB_NAME")
                }
                triggers {
                    pollSCM {
                        scmpoll_spec('* * * * *')
                    }
                }
                steps {
                    shell("make fclean")
                    shell("make")
                    shell("make tests_run")
                    shell("make clean")
                }
            }
            '''.stripIndent())
        }
    }
}
