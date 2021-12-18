#Script to calculate the overall average ratings-

from pyspark import SparkContext

sc = SparkContext.getOrCreate()

dataset = sc.textFile("hdfs:///user/testhadoopuser/ratings.csv").cache()
header = dataset.first()

cleaned_data = dataset.filter(lambda l: l != header)
ratings_data = cleaned_data.map(lambda l: l.split(",")[2])

total_ratings_sum = ratings_data.reduce(lambda a, b: float(a) + float(b))
total_ratings_count = ratings_data.count()

print("The overall average rating is: " + str(total_ratings_sum/total_ratings_count))

