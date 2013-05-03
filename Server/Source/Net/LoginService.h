#pragma once

namespace Net
{
	class LoginService
	{
	public:
		static LoginService& Instance();
		void Start();
	private:
		LoginService();
		~LoginService();
	};
}