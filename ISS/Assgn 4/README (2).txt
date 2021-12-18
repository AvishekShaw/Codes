Hi All,
The following tasks will help you get an idea on what to do in the assignment. It will be good if you can complete these before the tutorial on 22/11/2019-
---------------------------------------------------------------------------------------------------------------------------------
0. Check the contents of your folder on HDFS using the following command-
$ hdfs dfs -ls /user/<username>

Verify that the folder exists and is empty. The permissions on the folder are set such that only the concerned user can write to the folder. So please do not attempt to write to someone else's folders.
---------------------------------------------------------------------------------------------------------------------------------

1. A file- /scratch/ds221-2019/Tutorial3-Code/HDFSUploadFile.txt is a text file. Upload it to your folder using the following command-
$ hdfs dfs -put <filename with absolute path> [Eg. if you are in /home/johndoe and file is in /home/johndoe/data, type - hdfs dfs -put /home/johndoe/data/file.txt] 

This will copy the folder from your local path to your user folder on hdfs. Verify it has been uploaded using command in Step 0.
---------------------------------------------------------------------------------------------------------------------------------

2. Run the following example script- SparkPi.py by using the following command-
$ spark-submit --master yarn --deploy-mode cluster --queue default --num-executors 8 --executor-cores 1 --executor-memory 3G /scratch/ds221-2019/Tutorial3-Code/SparkPi.py

This code will calculate the value of Pi.
The different parameters passed here are - 

--master yarn : Sets YARN as the master URL (Resource Negotiator) for your spark program.
--deploy-mode cluster : Ensures your Job runs on Compute Nodes and not on the Head Node.
--queue default : Instructs YARN to schedule your application in the Default YARN Queue. [There are other methods of queuing as well]

The following parameters will ensure that the cluster is used fairly. YOU ARE EXPLICITLY RESTRICTED FROM CHANGING THESE PARAMETERS-
--num-executors 8 : Setting this to 8 instructs YARN to spawn 8 containers for your code.
--executor-cores 1 : Setting this to 1 instructs YARN to allocate 1 VCores to each of your container. (Each student will have access to 8 VCores)
--executor-memory 3G : Setting this to 3G instructs YARN to allocate 3GB of memory to each of your container. (Each student will have access to 24GB of total memory)


All print statements in the python code are logged in the YARN logs. TO access the YARN logs, type the following command- 
$ yarn logs --applicationId <application ID>


PLEASE NOTE THE FOLLOWING-

i. A student can access the application logs to the jobs only he/she has submitted. All other application logs are off-limits. 
ii. You need to submit the applicationID along with the python scripts for your assignment submission. Therefore, PLEASE SAVE THE APPLICATION ID for all successful jobs. 
iii. The YARN Application logs are huge files. To save time and get your required output, use the grep tool in linux which can find patterns in the document. To search Pi, type the following-

$ yarn logs --applicationId <application ID> | grep "Pi"
---------------------------------------------------------------------------------------------------------------------------------

3. There are two other Python scripts present in /scratch/ds221-2019/Tutorial3-Code/ with the following filenames-
a. MaxGenreMovie.py
b. AverageUserRating.py

These are the same programs that you were taught in class and thus will be familiar to you. 

Run both of these using the commands in Task (2) and get the application logs and extract the required values. We will verify the values in the tutorial tomorrow as well as go over the code and the individual commands.
---------------------------------------------------------------------------------------------------------------------------------

4.[Optional] Write a pyspark script to find how many distinct users have rated movies? [Use the dataset available at - /user/testhadoopuser/ratings.csv]

The instructions remain the same.

PLEASE MAIL ME IF THERE ARE ANY QUERIES.