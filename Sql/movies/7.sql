SELECT movies.title,ratings.rating from movies JOIN ratings on movies.id = ratings.movie_id where movies.year = 2010 ORDER BY ratings.rating DESC, movies.title ;