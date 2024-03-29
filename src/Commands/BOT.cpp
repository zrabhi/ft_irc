#include "Commands.hpp"
#include "../header.hpp"
#include <curl/curl.h>
#include <ostream>
#include <sstream>
#include <curl/curl.h>
#include <vector>

static size_t WriteCallback(char* ptr, size_t size, size_t nmemb, String* data)
{
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

String getQuote()
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (!curl)
        return "FAILURE";
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.quotationspage.com/random.php");
    String response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return "FAILURE";
    }
    String start_tag = "<a title=\"Click for further information about this quotation\" href=\"";
    String end_tag = "\">";
    String::size_type start_pos = response.find(start_tag);
    String::size_type end_pos = response.find(end_tag, start_pos + start_tag.length());
    if (start_pos == String::npos || end_pos == String::npos)
    {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return "FAILURE";
    }
    String quote_content = response.substr(end_pos + end_tag.length());
    String::size_type quote_end_pos = quote_content.find("</a>");
    if (quote_end_pos == String::npos)
    {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return "FAILURE";
    }
    String quote = quote_content.substr(0, quote_end_pos);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return quote;
}

String failedQuote() 
{
    Vector quotes;
    srand(time(0));
    quotes.push_back("The only way to do great work is to love what you do.");
    quotes.push_back("I am not a product of my circumstances. I am a product of my decisions.");
    quotes.push_back("Believe you can and you're halfway there.");
    quotes.push_back("If you want to live a happy life, tie it to a goal, not to people or things.");
    quotes.push_back("The best way to find yourself is to lose yourself in the service of others.");
    quotes.push_back("The greatest glory in living lies not in never falling, but in rising every time we fall.");
    quotes.push_back("Life is 10% what happens to us and 90% how we react to it.");
    quotes.push_back("Success is not final, failure is not fatal: it is the courage to continue that counts.");
    return quotes[rand() % quotes.size()];
}

bool    Commands::BOT(Vector params, Iterator &_client)
{
    (void)params;
    String response("");
    String quote = getQuote();
    if (quote == "FAILURE")
        quote = failedQuote();
    response += "300 RPL_NONE :" + quote + "\r\n";
    return (replyto(response, _client->first), true);
}
