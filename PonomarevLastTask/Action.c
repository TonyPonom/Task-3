Action()
{
	
	tName="03.OpenPage_Flight";
	lr_start_transaction(tName);

	status=web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	end_transaction(tName, status); //lr_think_time(3);
	needed =0;
	SeatCount=1;
	while(needed==0){
		tName="04.Create_Flight";
		lr_start_transaction(tName);
	
		web_reg_save_param_ex("ParamName=outboundFlight", 
    		"LB/IC= name=\"outboundFlight\" value=\"",
    		"RB/IC=\"",
    		"Notfound=warning",
    		"Ordinal=all",
    		LAST);

		web_reg_save_param_ex("ParamName=Price", 
    		"LB/IC=align=\"center\">$ ",
    		"RB/IC=</TD></TR>",
    		"Notfound=warning",
    		"Ordinal=all",
    		LAST);

		status=web_submit_data("reservations.pl", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=advanceDiscount", "Value=0", ENDITEM, 
			"Name=depart", "Value={City1}", ENDITEM, 
			"Name=departDate", "Value={Date1}", ENDITEM, 
			"Name=arrive", "Value={City2}", ENDITEM, 
			"Name=returnDate", "Value={Date2}", ENDITEM, 
			"Name=numPassengers", "Value=1", ENDITEM, 
			"Name=seatPref", "Value={SeatPref}", ENDITEM, 
			"Name=seatType", "Value={SeatType}", ENDITEM, 
			"Name=.cgifields", "Value=roundtrip", ENDITEM, 
			"Name=.cgifields", "Value=seatType", ENDITEM, 
			"Name=.cgifields", "Value=seatPref", ENDITEM, 
			"Name=findFlights.x", "Value=59", ENDITEM, 
			"Name=findFlights.y", "Value=6", ENDITEM, 
			LAST);
	
		end_transaction(tName, status); //lr_think_time(3);
	
		for(count=1;count<=4;count++){
			lr_output_message(lr_eval_string(lr_paramarr_idx("Price",count)));
			if((atoi(lr_eval_string(lr_paramarr_idx("Price",count))) >= 100)&&(atoi(lr_eval_string(lr_paramarr_idx("Price",count))) <= 500)){
		   		needed = count;
		   	}
		}
	
		if(needed==0){
			SeatCount++;
			lr_next_row("SeatType.dat");
		}
	
		if(SeatCount>3){
			SeatCount=1;
			lr_next_row("City1.dat");
		}
	
		lr_output_message("         ");
	
	}
	
	lr_output_message("selected %d",needed);
	lr_save_string(lr_eval_string(lr_paramarr_idx("outboundFlight",needed)),"fligh");
	
	tName="05.Create_ChooseCostAndTime";
	lr_start_transaction(tName);

	status=web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={fligh}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=58", ENDITEM, 
		"Name=reserveFlights.y", "Value=12", ENDITEM, 
		LAST);

	end_transaction(tName, status); //lr_think_time(3);
	tName="06.Create_PaymentlDetails";
	lr_start_transaction(tName);
	
	status=web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value=Jojo", ENDITEM, 
		"Name=lastName", "Value=Bean", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=pass1", "Value=Jojo Bean", ENDITEM, 
		"Name=creditCard", "Value=", ENDITEM, 
		"Name=expDate", "Value=", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=outboundFlight", "Value={fligh}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=43", ENDITEM, 
		"Name=buyFlights.y", "Value=4", ENDITEM, 
		LAST);
	
	end_transaction(tName, status); //lr_think_time(3);
	
	
	
	return 0;
}
