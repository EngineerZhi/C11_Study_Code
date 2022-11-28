//#include "signalcpp.h"
//
//MsgInstanceServer* MsgInstanceServer::m_Instance = nullptr;
//MsgInstanceServer::CGarbo m_Garbo;
//std::mutex   MsgInstanceServer::m_Mutex;
//MsgInstanceServer*        MsgInstanceServer::instance()
//{
//	if (m_Instance == nullptr) {
//		std::lock_guard<std::mutex> lck(m_Mutex);
//		if (m_Instance == nullptr) {
//			m_Instance = new MsgInstanceServer();
//		}
//	}
//	return m_Instance;
//}
//MsgInstanceServer::MsgInstanceServer() {
//	std::cout << __FUNCTION__ << std::endl;
//
//}
//MsgInstanceServer::~MsgInstanceServer() {
//	std::cout << __FUNCTION__ << std::endl;
//}
//const std::string MsgInstanceServer::GetToken()
//{
//	std::cout << __FUNCTION__ << std::endl;
//	return std::string("123+token");
//}
////À¬»ø»ØÊÕÆ÷
//MsgInstanceServer::CGarbo::CGarbo() {
//	std::cout << __FUNCTION__ << std::endl;
//}
//MsgInstanceServer::CGarbo::~CGarbo()
//{
//	std::cout << __FUNCTION__ << std::endl;
//	if (m_Instance != nullptr) {
//		std::cout << "m_Instance is not  empty" << std::endl;
//		delete m_Instance;
//		m_Instance = nullptr;
//	}
//}
