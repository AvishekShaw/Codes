no 2.5.3                                         File: MaxGenreMovie.py                                                                                        

#Script to identify the movie which has the maximum genres
from pyspark import SparkContext

sc = SparkContext.getOrCreate()
dataset = sc.textFile("hdfs:///user/testhadoopuser/movies.csv").cache()

header = dataset.first() // returns the first row into a new RDD
cleaned_data = dataset.filter(lambda l: l != header) // returns a new RDD without the first line

csv_data = cleaned_data.map(lambda l: l.split(",")) 
genre_count_data = csv_data.map(lambda l: (len(l[2].split("|")), l))

max_genre_count_value = genre_count_data.max()[0]
max_genre_movie_record = genre_count_data.lookup(max_genre_count_value)

print("The movie with the max Genre Count is: " + str(max_genre_movie_record))
`
