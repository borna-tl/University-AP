#include <string>
#include <sstream>
#include "handlers.hpp"
using namespace std;

Response *SignupForm::callback(Request *req) {
    if (sessions->find(req->getSessionId()) != sessions->end())
        return Response::redirect("/home");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
    << "<html>" << endl
    << "<head><title>Signup Form</title>" << endl
    << "<style>"
    << "a:link, a:visited {"
    << "background-color: tomato;"
    << "color: white;"
    << "padding: 15px 25px;"
    << "text-align: center;"
    << "text-decoration: none;"
    << "display: inline-block;"
    << "}"
    << "a:hover, a:active {"
    << "background-color: red;"
    << "}"
    << "</style>"
    << "</head>"
    << "<body style='background-color: orange; text-align: center;'>" << endl
    << "<div style='background-color:tomato;color:white;padding:1px;'>"
    << "<h1>Please fill the form below</h1>" << endl
    << "</div>"
    << "<br /> <br />"
    << "<form action='/check_signup' method='get'>" << endl
    << "<input name='username' type='text' placeholder='Username' />" << "<br />" << endl
    << "<input name='password' type='text' placeholder='Password' />" << "<br />" << endl
    << "<input name='passwordcopy' type='text' placeholder='Password Copy' />" << "<br />" << endl
    << "<input name='email' type='text' placeholder='Email' />" << "<br />" << endl
    << "<button type='submit' >Signup!</button>" << endl
    << "</form>" << endl
    << "</div>" << endl;
    if (status->has_signup_errors()){
        if (status->used_username){
            body
            << "<div style='background-color:tomato;color:white;padding:1px;'>"
            << "<p>&#10071 Username already taken.</p>" << endl
            << "</div>"
            << "<br />";
        }
        if (status->wrong_password_copy){
            body
            << "<div style='background-color:tomato;color:white;padding:1px;'>"
            << "<p>&#10071 Password and Password copy don't match.</p>" << endl
            << "</div>"
            << "<br />";
        }
        status->reset();
    }
    body
    << "</body>" << endl
    << "</html>" << endl;
    res->setBody(body.str());
    return res;
}

Response *ShowDynamicHome::callback(Request *req) {
    if (sessions->find(req->getSessionId()) != sessions->end())
        return Response::redirect("/home");
    else {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        ostringstream body;
        body
        << "<html>" << endl
        << "<head><title>Login Required</title>" << endl
        << "<style>"
        << "a:link, a:visited {"
        << "background-color: tomato;"
        << "color: white;"
        << "padding: 15px 25px;"
        << "text-align: center;"
        << "text-decoration: none;"
        << "display: inline-block;"
        << "}"
        << "a:hover, a:active {"
        << "background-color: red;"
        << "}"
        << "</style>"
        << "</head>"
        << "<body style='background-color: orange; text-align: center;'>" << endl
        << "<div style='background-color:tomato;color:white;padding:1px;'>"
        << "<h1>You need to login first!</h1>" << endl
        << "</div>"
        << "<br /> <br />" << endl
        << "<a href='/login'>Login</a>" << endl
        << "<br /> <br />" << endl
        << "<a href='/signup'>Signup</a>" << endl;
        if (status->has_logged_out){
            body
            << "<br /> <br /> <br />" << endl
            << "<div style='background-color:tomato;color:white;padding:1px;'>"
            << "<p>&#9989 Logout Successful.</p>" << endl
            << "</div>";
            status->reset();
        }
        body
        << "</body>" << endl
        << "</html>" << endl;
        res->setBody(body.str());
        return res;
    }
    
}

Response *CheckSignup::callback(Request *req) {
    string username = req->getQueryParam(USERNAME_KEYWORD);
    string password = req->getQueryParam(PASSWORD_KEYWORD);
    string password_copy = req->getQueryParam(PASSWORD_KEYWORD);
    string email = req->getQueryParam(EMAIL_KEYWORD);
    status->used_username = app->can_signup_user(username) ? false : true;
    status->wrong_password_copy = (password == password_copy) ? false : true;
    if (!status->has_signup_errors()){
        User* user = app->signup_user(username, password_copy, email);
        Response *res = Response::redirect("/home");
        res->setSessionId(username);
        sessions->insert(make_pair(username, user));
        return res;
    }
    else{
        return Response::redirect("/signup");
    }
}
Response *ShowLoggedinHome::callback(Request *req){
    if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
    << "<!DOCTYPE html>"
    << "<html>"
    << "<head>"
    << "<title> Home </title>"
    << "<style>"
    << "ul {"
    << "list-style-type: none;"
    << "margin: 0;"
    << "padding: 0;"
    << "overflow: hidden;"
    << "background-color: orange;"
    << "}"

    << "li {"
    << "float: left;"
    << "}"

    << "li a {"
    << "display: block;"
    << "color: white;"
    << "text-align: center;"
    << "padding: 14px 16px;"
    << "text-decoration: none;"
    << "}"

    << "li a:hover:not(.active) {"
    << "background-color: tomato;"
    << "}"

    << ".active {"
    << "background-color: tomato;"
    << "}"
    << "</style>"
    << "</head>"
    << "<body>"

    << "<ul>"
    << "<li><a href='/home'>Home</a></li>"
    << "<li><a href='/wallet'>Wallet</a></li>"
    << "<li style='float:right'><a class='active' href='/logout'>&#128100 Logout "
    << sessions->find(req->getSessionId())->second->get_name() << "</a></li>"
    << "</ul>"

    << "</body>"
    << "</html>"

    << "<!DOCTYPE html>"
    << "<html>"
    << "<head>"
    << "<style>"
    << "div.gallery {"
    << "margin: 5px;"
    << "border: 1px solid #ccc;"
    << "float: left;"
    << "width: 300px;"
    << "}"

    << "div.gallery:hover {"
    << "border: 1px solid #777;"
    << "}"

    << "div.gallery img {"
    << "width: 300px;"
    << "height: 300px;"
    << "}"

    << "div.desc {"
    << "padding: 10px;"
    << "text-align: center;"
    << "}"
    << "</style>"
    << "</head>"
    << "<body>"
    << "<form action='/home'>"
    << "<label for='quantity_min' style='color:tomato;'>Star Filter  </label>"
    << "<input type='number' id='quantity_min' name='min_star' min='1' max='5' placeholder='(between 1 and 5)'>"
    << "<input type='number' id='quantity_max' name='max_star' min='1' max='5' placeholder='(between 1 and 5)'>"
    << "<input type='submit' value='Filter' style='color:tomato'>"
    << "</form>";
    int max_star = 5, min_star = 1;
    if (req->getQueryParam(MIN_STAR_KEYWORD) != "" && req->getQueryParam(MAX_STAR_KEYWORD) != ""){
        min_star = stoi(req->getQueryParam(MIN_STAR_KEYWORD));
        max_star = stoi(req->getQueryParam(MAX_STAR_KEYWORD));
    }
    body << app->get_hotels_list_html(min_star, max_star);
    body
    << "</body>"
    << "</html>";
    res->setBody(body.str());
    return res;
}

Response *ShowLoginForm::callback(Request *req){
    if (sessions->find(req->getSessionId()) != sessions->end())
        return Response::redirect("/home");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
    << "<html>" << endl
    << "<head><title>Login Form</title>" << endl
    << "<style>"
    << "a:link, a:visited {"
    << "background-color: tomato;"
    << "color: white;"
    << "padding: 15px 25px;"
    << "text-align: center;"
    << "text-decoration: none;"
    << "display: inline-block;"
    << "}"
    << "a:hover, a:active {"
    << "background-color: red;"
    << "}"
    << "</style>"
    << "</head>"
    << "<body style='background-color: orange; text-align: center;'>" << endl
    << "<div style='background-color:tomato;color:white;padding:1px;'>"
    << "<h1>Please fill the form below</h1>" << endl
    << "</div>"
    << "<br /> <br />"
    << "<form action='/check_login' method='get'>" << endl
    << "<input name='username' type='text' placeholder='Username' />" << "<br />" << endl
    << "<input name='password' type='text' placeholder='Password' />" << "<br />" << endl
    << "<button type='submit' >Login!</button>" << endl
    << "</form>" << endl
    << "</div>" << endl;
    if (status->has_login_errors()){
        if (status->wrong_username_or_password){
            body
            << "<div style='background-color:tomato;color:white;padding:1px;'>"
            << "<p>&#10071 Username/Password incorrect.</p>" << endl
            << "</div>"
            << "<br />";
        }
        status->reset();
    }
    body
    << "</body>" << endl
    << "</html>" << endl;
    res->setBody(body.str());
    return res;
}
Response *CheckLogin::callback(Request *req){
    string username = req->getQueryParam(USERNAME_KEYWORD);
    string password = req->getQueryParam(PASSWORD_KEYWORD);
    status->used_username = app->can_signup_user(username) ? false : true;
    if (status->used_username){
        User* user = sessions->find(username)->second;
        if (user->same_password(password)){
            Response *res = Response::redirect("/home");
            res->setSessionId(username);
            app->login_user(username);
            return res;
        }
    }
    status->wrong_username_or_password = true;
    return Response::redirect("/login");
}
Response *CheckLogout::callback(Request *req){
    Response *res = Response::redirect("/");
    res->setSessionId("");
    app->logout_user();
    status->has_logged_out = true;
    return res;
}
Response *ShowWallet::callback(Request *req){
    if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
    ostringstream body;
    body
    << "<!DOCTYPE html>"
    << "<html>"
    << "<head>"
    << "<style>"
    << "ul {"
    << "list-style-type: none;"
    << "margin: 0;"
    << "padding: 0;"
    << "overflow: hidden;"
    << "background-color: orange;"
    << "}"

    << "li {"
    << "float: left;"
    << "}"

    << "li a {"
    << "display: block;"
    << "color: white;"
    << "text-align: center;"
    << "padding: 14px 16px;"
    << "text-decoration: none;"
    << "}"

    << "li a:hover:not(.active) {"
    << "background-color: tomato;"
    << "}"

    << ".active {"
    << "background-color: tomato;"
    << "}"
    << "</style>"
    << "</head>"
    << "<body>"

    << "<ul>"
    << "<li><a href='/home'>Home</a></li>"
    << "<li><a href='/wallet'>Wallet</a></li>"
    << "<li style='float:right'><a class='active' href='/logout'>&#128100 Logout "
    << sessions->find(req->getSessionId())->second->get_name() << "</a></li>"
    << "</ul>"
    << "<br /> <br />"
    << "</body>"
    << "</html>";
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string wallet_html = sessions->find(req->getSessionId())->second->show_wallet_html(status->wallet_update_status);
    res->setBody(body.str() + wallet_html);
    status->reset();
    return res;
}
Response *CheckWallet::callback(Request *req){
    string amount_s = req->getQueryParam(AMOUNT_KEYWORD);
    double amount = stod(amount_s);
    if (amount <= 0)
        status->wallet_update_status = 1;
    else{
        status->wallet_update_status = 2;
        sessions->find(req->getSessionId())->second->charge_wallet(amount);
    }
    return Response::redirect("/wallet");
}

Response *ShowHotel::callback(Request *req){
    if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
    string hotel_id = req->getQueryParam(ID_KEYWORD);
    Hotel* hotel = app->find_hotel_by_id(hotel_id);
    ostringstream body;
    body << hotel->get_rooms_table_html(sessions->find(req->getSessionId())->second->get_name());
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(body.str());
    status->reset();
    return res;
}