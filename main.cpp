
#include <iostream>
#include <Windows.h>
#include <vector>

#pragma region CLASS_STRUCT
struct Vector3
{
    float x, y, z;
};

class StopWatch
{
    LARGE_INTEGER freq;
    LARGE_INTEGER start, end;

public:
    StopWatch()
    {
        QueryPerformanceFrequency(&freq);
    }

    void Start()
    {
        QueryPerformanceCounter(&start);
    }

    void Stop()
    {
        QueryPerformanceCounter(&end);
    }

    double ElapseTime() const
    {
        return static_cast<double>(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    }
};

class ScopedStopWatch
{
private:
    StopWatch& m_StopWatch;

public:
    ScopedStopWatch(StopWatch& StopWatch) : m_StopWatch(StopWatch)
    {
        m_StopWatch.Start();
    }
    ~ScopedStopWatch()
    {
        m_StopWatch.Stop();
    }
};

struct Out
{
	static void PrintElapsed(const char* Msg, const StopWatch& Sw)
	{
        printf("%20s: %10lf[ms]\n", Msg, Sw.ElapseTime());
	}
};
#pragma endregion

int main()
{
    const int Elem = 10000000;
    const int Size = Elem * sizeof(Vector3);
    std::vector<Vector3> Src;
    Src.resize(Elem);
    Vector3* pSrc = &Src[0];

    StopWatch sw;
    
    std::vector<Vector3> Dst1;
    std::vector<Vector3> Dst2;
    std::vector<Vector3> Dst3;
    std::vector<Vector3> Dst4;
    std::vector<Vector3> Dst5;
    std::vector<Vector3> Dst6;
    std::vector<Vector3> Dst7;
    Dst1.resize(Elem);
    Dst2.resize(Elem);
    Dst3.resize(Elem);
    Dst4.resize(Elem);
    Dst5.resize(Elem);
    Dst6.resize(Elem);
    Dst7.resize(Elem);

    {
        ScopedStopWatch _ssw(sw);
        for (int i = 0; i < Elem; i++)
        {
            Dst1[i].x = pSrc[i].x;
            Dst1[i].y = pSrc[i].y;
            Dst1[i].z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("vector[] i++", sw);
    

    {
        ScopedStopWatch _ssw(sw);
        for (int i = 0; i < Elem; ++i)
        {
            Dst2[i].x = pSrc[i].x;
            Dst2[i].y = pSrc[i].y;
            Dst2[i].z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("vector[] ++i", sw);

    {
        ScopedStopWatch _ssw(sw);
        Vector3* pVec = &(Dst3[0]);
        for (int i = 0; i < Elem; i++)
        {
            pVec[i].x = pSrc[i].x;
            pVec[i].y = pSrc[i].y;
            pVec[i].z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("pointer i++", sw);

    {
        ScopedStopWatch _ssw(sw);
        Vector3* pVec = &(Dst4[0]);
        for (int i = 0; i < Elem; ++i)
        {
            pVec[i].x = pSrc[i].x;
            pVec[i].y = pSrc[i].y;
            pVec[i].z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("pointer ++i", sw);

    {
        ScopedStopWatch _ssw(sw);
        for (int i = 0; i < Elem; i++)
        {
            Vector3& refVec = Dst5[i];
            refVec.x = pSrc[i].x;
            refVec.y = pSrc[i].y;
            refVec.z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("loop ref i++", sw);

    {
        ScopedStopWatch _ssw(sw);
        for (int i = 0; i < Elem; ++i)
        {
            Vector3& refVec = Dst6[i];
            refVec.x = pSrc[i].x;
            refVec.y = pSrc[i].y;
            refVec.z = pSrc[i].z;
        }
    }
    Out::PrintElapsed("loop ref ++i", sw);

    {
        ScopedStopWatch _ssw(sw);
        memcpy(&Dst7[0], &Src[0], Size);
    }
    Out::PrintElapsed("memcpy", sw);

    getchar();
    return 0;
}
