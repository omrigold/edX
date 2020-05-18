select title, rating
from ratings r
join movies m
  on m.id = r.movie_id
where year = 2010
order by rating desc, title asc;