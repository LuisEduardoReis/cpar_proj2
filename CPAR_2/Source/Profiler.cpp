#include "Profiler.h"

using namespace CPAR;
using namespace std;
using namespace std::chrono;

void Profiler::Start()
{
	m_start = high_resolution_clock::now();
}

void Profiler::End()
{
	m_end = high_resolution_clock::now();
}
