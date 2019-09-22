#include "MyForm.h"
#include <stdio.h>
#include <conio.h>
#include "ArrayTypes.h"	
#include "Wrapper.h"
#include "windows.h"
using namespace Project1;
[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm());
	return 0;
}