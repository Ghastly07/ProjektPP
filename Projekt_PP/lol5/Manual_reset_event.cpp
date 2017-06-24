//#include "Manual_reset_event.h"
//
//
//
//Manual_reset_event::Manual_reset_event(bool signaled = false) :signaled_(signaled)
//{
//}
//
//
//Manual_reset_event::~Manual_reset_event()
//{
//}
//
//void Manual_reset_event::set()
//{
//	{
//		boost::lock_guard<boost::mutex> lock(m_);
//		signaled_ = true;
//	}
//
//	// Notify all because until the event is manually
//	// reset, all waiters should be able to see event signalling
//	cv_.notify_all();
//}
//
//void Manual_reset_event::unset()
//{
//	boost::lock_guard<boost::mutex> lock(m_);
//	signaled_ = false;
//}
//
//void Manual_reset_event::wait()
//{
//	
//	//boost::lock_guard<boost::mutex> lock(m_);
//	boost::mutex::scoped_lock lock(m_);
//
//
//	bool worker_is_done = false;
//
//	while (!signaled_)
//	{
//		cv_.wait(lock, [&worker_is_done] {return worker_is_done; });
//	}
//}
