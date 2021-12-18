# This is for Question 3 of Assgn4 for DS 221.
# we need to use the files ratings and movies.
# Ratings file has as columns : UserID, movieID, rating, timestamp
from pyspark import SparkContext

"""
movies1=sc.textFile("hdfs:///user/simmhan/ml/small/movies.csv").cache()
movies2=movies1.map(lambda l: l.split(","))
movies=movies2.map(lambda l:(l[0],l[2]))
"""

ratings1=sc.textFile("hdfs:///user/simmhan/ml/small/ratings.csv").cache()
ratings2=ratings1.map(lambda l:l.split(","))
ratings=ratings2.map(lambda l:(l[1],l[0])) # this has movieID and userID arranged in that order
header=ratings.first()
ratings_cleaned=ratings.filter(lambda l:l!=header)






