#ifndef BJEXCEPTION_HH
#define BJEXCEPTION_HH
class bjException{
	public:
		bjException(const char* name):_what(name){}
		const char* what(){return _what.c_str();}
	private:
		std::string _what;
};
std::ostream& operator <<(std::ostream& os, const bjException bje){
	return(os<<"\033[1;31mERROR!\033[0m");
}
#endif
