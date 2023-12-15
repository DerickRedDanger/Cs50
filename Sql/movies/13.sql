select people.name from people join stars join movies on movies.id = stars.movie_id AND people.id = stars.person_id where people.name != "Kevin Bacon" and movies.title
IN
(
    select movies.title from people join stars join movies on movies.id = stars.movie_id AND people.id = stars.person_id where people.name = "Kevin Bacon" and people.birth = 1958
    );