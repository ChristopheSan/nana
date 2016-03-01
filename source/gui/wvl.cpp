/*
 *	Nana GUI Library Definition
 *	Copyright(C) 2003-2015 Jinhao(cnjinhao@hotmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0. 
 *	(See accompanying file LICENSE_1_0.txt or copy at 
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *	@file: nana/gui/wvl.cpp
 *	@description:
 *		the file contains the files required for running of Nana.GUI 
 */

#include <nana/gui/wvl.hpp>
#include <nana/gui/detail/bedrock.hpp>
#include <thread>

#include <iostream> 


//#define NANA_AUTOMATIC_GUI_TESTING

inline unsigned Wait(unsigned wait = 0)
{
#ifdef NANA_AUTOMATIC_GUI_TESTING
	return wait;
#else
	return 0;
#endif
}

namespace nana
{
	namespace detail
	{
		void form_loader_private::insert_form(::nana::widget* p)
		{
			bedrock::instance().manage_form_loader(reinterpret_cast<basic_window*>(p->handle()), true);
		}
	}

	void exec(unsigned wait, std::function<void()> f )
	{
		#ifdef NANA_ADD_DEF_AUTOMATIC_GUI_TESTING
				if (!wait)
					wait = 10;
				if (!f)
					f = []() {API::exit(); };
		#endif

		wait = Wait(wait);

		std::cout << "Will wait " << wait << " sec...\n";
		std::thread t([wait, &f]() 
		              { if (wait) 
		                   {   
							   std::cout << "Waiting " << wait << " sec...\n";
							   std::this_thread::sleep_for(std::chrono::seconds{ wait } ); 
							   std::cout << "Waited !! running... \n"  ;
		                       f(); 
							   //API::exit();
							   std::cout << "Runed... \n";
		                   }
		              });
		
		detail::bedrock::instance().pump_event(nullptr, false);

		if (t.joinable())
			t.join();
	}
}//end namespace nana
