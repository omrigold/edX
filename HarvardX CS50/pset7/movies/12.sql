select m.title
from movies m
join stars s
  on m.id = s.movie_id
join people p
  on p.id = s.person_id
join (select m.id
     from movies m
     join stars s
       on m.id = s.movie_id
     join people p
       on p.id = s.person_id
     where p.name = "Helena Bonham Carter") m2
  on m2.id = m.id
where p.name = "Johnny Depp"
;