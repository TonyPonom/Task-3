vuser_end()
{
	tName="07.SignOff";
	lr_start_transaction(tName);
	
	status=web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);
	
	end_transaction(tName, status); //lr_think_time(3);
	
	return 0;
}
