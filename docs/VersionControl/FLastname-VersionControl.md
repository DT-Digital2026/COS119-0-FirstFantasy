# Instructions

Update this document where indicated [look for the brackets!]. Replace text inside the brackets with your own information. For example: Course Name should be the name of this course, and not the generic words "Course Name".

<br>

## [ COS119-0 <-- Project and Portfolio 1 ]

- **[ Brad Wtson ]**
- **[ 10/4 ]**

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.

Update the information below to demonstrate your knowledge on this topic.

**1. Using Terminal, there are essential commands to know.**

List the correct Terminal commands to do the actions listed below. Replace **CMD** with the correct command sequence. You can keep or enhance the brief description.

**The last bullet provides an example**.

- [ clear ]: Clear the Screen
- [ pwd ]: Print the "Working Directory"
- [ ls ]: List files and folders
- [ ls -a ]: List files and folders, including invisible files
- [ ls -alh]: List all files and folders, in human readable form
- [ cd <directory> ]: Change directory
- [ cd / ]: Change directory, go to root directory
- [ cd ~ ]: Change directory and go to user home directory
- [ cd .. ]: Change directory, go up one folder level
- [ cd ../.. ]: Change directory, go up two folder levels
- [ cd ~/Desktop ]: Change directory to my desktop!

**2. Using Terminal...**

**Folder Drop:** Try typing "cd" followed by a space, and then drag a folder into terminal and press return. Test this out and describe your results below.

[ Dragging the folder into the Terminal window automatically entered the folder's full path after the cd command. After pressing enter, Terminal changed the 
working directory to the folder I dragged in. I verified the change by using the pwd command. ]

## Topic: Version Control & Git

Version control, also known as revision control, records changes to a file or set of files over time so that you can recall specific versions later. In this class, we are learning Git. Update the information below where indicated.

**1. There are three types of version control.**

[ Local Version Control - Stores different versions of the files directly on the user's local computer. This allows the user to return to an earlier version, but
							it does not provide an easy way to collaborate with other developers. 
							
  Centralized Version Control - Stores project files and their version history on one central server. Multiple developers can access and update the same project
							but they depend on central server being available.
							
  Distributed Version Control - Gives each developer a complete copy of the repository, including its own version history. Developers can work locally and then share
							their changes with others. Git is a distributed version control system.]

**2. Using Terminal, there are also essential Git commands to know.**

List the correct Git commands to do the actions listed below in Terminal. Replace CMD with the correct command and keep or enhance the brief description.

- [ git clone <repository-url> ]: Clone a repository
- [ git config --global user.name "Your Name"]: Set-up a global user name
- [ git config --global user.email "testemail@email.com ]: Set-up a global email address (to match my GitHub account email)
- [ git status ]: Shows the current state of your directory and staging area
- [ git add . ]: Add modified files to the next commit
- [ git commit -m "test commit message" ]: Make a commit with a new message
- [ git log ]: Show my commit history
- [ git help ]: Show Git's help screen

**3. Connecting to GitHub using Terminal.**
HTTPS is the the correct way to connect to GitHub in this course. Describe how you connect to GitHub from Terminal using this protocol. What steps do you take?

[ To connect to a Git repo using HTTPS, I first go to the repo on Git and click the Code button. I select HTTPS and copy the repo URL. In terminal, I navigate to the
folder where I want the repo stored using the cd command. I then type 'git clone' followed by the HTTPS URL: 

git clone https://github.com/USERNAME/REPOSITORY.git

Git will download the repo to my computer and create a local copy. I can then use 'cd REPOSITORY' to enter the repo folder and use Git commands such as 'git status', 'git add', 
'git commit', 'git pull', and 'git push' to work with the repository. When authentication is required Git will use secure authentication rather than using my Git password automatically.]

**4. Using .gitignore and Why it's Important**  
Most repositories contain a .gitignore file.

- What is the purpose of this file?
  <br>
  [The .gitignore file tells Git which files and folders should not be tracked or committed to the repo. This helps prevent unnecessary, temporary, generated, or sensitive
  files from being added to the project.]

- What is the "**.DS_Store**" file and why would you want to ignore it?
  <br>
  [.DS_Store is a hidden file that is automatically created by macOS Finder. It stores information about how a folder is displayed, such as icon positions and view settings. 
  It does not contain usefule project code, so it should normally be ignored to prevent unnecessary files from being committed to the report. ]

- What other file or folder would you want to add to a .gitignore file and why?
  <br>
  [For a C++ Visual Studio project, I would add the generated folders such as .vs/, Debug/, Release/, and x64/ to .gitignore. These folders contain temporary files, build 
  output, and settings generated by Visual Studio. They can be recreated by the development environment and do not need to be stored in the repo. ]

<br>

# Reference Links

Replace the example references below with your own links and recommended resources. It is acceptable to provide multiple links for a single topic and to use material provided to you in this class. You are encouraged to link to your own independent research as well.

[ Research Summary: What resource(s) did you find most helpful this past week and why? ]

**Terminal Commands**  
[https://www.gnu.org/software/bash/manual/bash.html](https://www.gnu.org/software/bash/manual/bash.html)

**Three Types of Version Control**  
[https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control.html](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control.html)

**Git Commands**  
[https://git-scm.com/docs](https://git-scm.com/docs)

**Connecting to GitHub using Terminal**  
[https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

**Using .gitignore and Why it's Important**  
[https://git-scm.com/docs/gitignore](https://git-scm.com/docs/gitignore)
