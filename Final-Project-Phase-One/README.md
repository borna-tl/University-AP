# AP-Final-Project-Phase1
A simple implementation of a hotel application; 
to execute simply run "./utrip.out Hotels.csv" 

# What you can do:

POST signup ? email < email > username < username > password < password >
* to signup using email, username and a password

POST login ? email < email > password < password >
* to login using email and password

POST logout

POST wallet ? amount < amount >
* to charge your wallet a certain amount

GET wallet ? count < count >
* to get your wallet transactions

GET hotels
* to show a list of all the hotels

GET hotels ? id <id>
* to get the properties of a specific hotel
 
POST filters ? city <city>
* to filter hotels by city

POST filters ? min_star <min_star> max_star <max_star>
* to filter hotels by their star rating

POST filters ? min_price <min_price> max_price <max_price>
* to filter hotels by their average room cost

POST filters ? type <room_type> quantity <quantity> check_in <check_in> check_out <check_out>
* to filter hotels by their available rooms
  
DELETE filters

POST reserves ? hotel <hotel_id> type <room_type> quantity <quantity> check_in <check_in> check_out <check_out>
* to reserve a number of rooms from a hotel on a specific date
  
GET reserves
* to view your reservations

DELETE reserves ? id <reservation_id>
* to cancel a specific reservation

POST comments ? hotel <hotel_id> comment <comment>
* to comment about a hotel
  
POST ratings ? hotel < hotel > location < location > cleanliness < cleanliness > staff < staff > facilities < facilities > value_for_money < Value_for_money > overall_rating < overall_rating >
* to rate a hotel

GET comments ? hotel <hotel_id>
* to view comments on a selected hotel

GET ratings ? hotel < hotel_id >
* to view the average users rating of a selected hotel
