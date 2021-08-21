# AP-OOP-Project
A Simple Object Oriented Program for my Advanced Programming class - Spring 2020
This Program reads some goodreads .csv files using "./Goodreads.out Assets" and supports the following commands  

#1 show_author_info <author_id>

#2 show_sorted_shelf <user_id> <shelf_type> <genre>
* <shelf_type> ∈ {read, want_to_read, currently_reading}
  
#3 credit <user_id>
* calculates user's credit with the following algorithm
user_credit = 1/2 x [(number_of_user_reviews_likes / number_of_likes) + (number_of_user_reviews / number_of_reviews)]

#4 best_book
* shows the highest rating book

#5 best_reviewer
* shows the highest rating reviewer

#6 recommend_first_approach <user_id>
* recommends the book with the highest score to the user using the following algorithm
rating = Σ(review_rating × review_user_credit) / number_of_reviews_of_book
favorite_genres = 5, if book and user favorites have genres in common.
favorite_genres = 0, otherwise
score = rating + favorite_genres

#7 recommend_second_approach <user_id>
* for each of the users the given user follows, this code will calculate the top 3 books with the highest score (using the #6 algorithm)
once the list of all the highest ranking books is completed, this program will recommend the most common book from that list.
NOTE that if user A follows user B, and user B follows user C. then C is considered amongst the users which user A follows.
