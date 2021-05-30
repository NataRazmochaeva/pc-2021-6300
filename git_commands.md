## You can get description for all git commands
```git 
git --help
```
## First time you should clone repo in your local directory
```git 
git clone https://github.com/NataRazmochaeva/pc-2021-6300.git
```
## After cloning you should go into git reposiroty directory
```git 
cd pc-2021-6300
```
## Default you in main branch, please create your own branch for homework
```git 
git checkout -b steven-rodgers-hw1
```
## In your branch you should create directory (locally in your laptop) for storing your own source code files. You also can do this using your File Manager
```git 
mkdir steven-rodgers-hw1
```
## Ask git to show you shanges what you did in git repository directory. it can help you to understand what is happening in git "mind"
```git 
git status
```
## After you placed your own source code in your own directory (you also can do this using File Manager in your OS), you should ask git to index your changes
```git 
git add steven-rodgers-hw1/
```
## Here you can do "git status" again to be sure that git started to watching on your files
```git 
git status
```
## After that you should to create commit -- special node for git control version system
```git 
git commit -m "steven-rodgers-hw1"
```
## After that all is ready to send your changes in remote repository. You can do this using next command
```git 
git push --set-upstream origin steven-rodgers-hw1
```
## After that you can go to https://github.com/NataRazmochaeva/pc-2021-6300 and to create new pull request using green button on site 

## For every new homework CREATE NEW BRANCH ONLY FROM MAIN BRANCH :
```git 
git checkout main
```
```git 
git checkout -b <new_branch_name>
```

# FAQ
## Login problems 
Sometimes git says that it doesn't know you yet, you can say who you are using login commands:
```git 
git config --global user.name "your_username"
```
```git 
git config --global user.email "your_email_address@example.com"
```
## Push problems
Sometimes git will reject your push command. It usually happens when changes were done in remote repository by somebody. It is absolutely normal case. Before creating, for example, your folder for HW-2 you should do git pull command for getting remote changes into your local repository. 
```git 
git pull
```
After push command in your loсal repository files and folders of your classmates will appear. Please, dont remove and do not any changes in your classmates files and folders.
