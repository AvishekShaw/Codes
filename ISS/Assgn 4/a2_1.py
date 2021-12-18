# This is for Question 1 of Assgn4 for DS 221.
# we need to use the files ratings and movies.
from pyspark import SparkContext

ratings1=sc.textFile("hdfs:///user/simmhan/ml/small/ratings.csv").cache()
ratings2=ratings1.map(lambda l:l.split(","))
ratings=ratings2.map(lambda l:(l[1],l[2]))
