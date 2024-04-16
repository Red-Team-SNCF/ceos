#include "ceos.h"

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR szArgs, _In_ int nCmdShow)
#endif

{

	ceosMain();

	return 0;
}