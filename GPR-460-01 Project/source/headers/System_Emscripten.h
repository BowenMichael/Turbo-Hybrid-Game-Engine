

namespace TurboHybrid {
	typedef char* string;
	
	class System
	{
	public:
		void Init();
		void Shutdown();
		void ShowError(const TurboHybrid::string& message);
		void LogToErrorFile(const TurboHybrid::string& message);
	protected:
	private:

	};
}
