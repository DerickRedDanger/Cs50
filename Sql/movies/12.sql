select title from people join stars join movies on movies.id = stars.movie_id AND people.id = stars.person_id where people.name = "Helena Bonham Carter" and movies.title
IN
(
    select title from people join stars join movies on movies.id = stars.movie_id AND people.id = stars.person_id where people.name = "Johnny Depp"
    );