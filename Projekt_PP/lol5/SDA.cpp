//
//macin - imgin[x, y]
//SX, SY - width and height of input / output image,
//R - (oating point) radius of neighborhood
//min_roznica(threshold) - the optional dierence to be checked(especially for noisy
//	images).
#include"SDA.h"

int SDA::MaxCPU = 4;
int SDA::remaining = 1;

public ref class TaskInfo
{
public:


	int sx, sy, min_roznica, N/*,remaining*/;
	array< double, 2 >^mact = nullptr;
	array< double, 2 >^macout = nullptr;
	ManualResetEvent ^mre;
	int nextIteration, r2, exclusiveUpperBound;
	

	TaskInfo(int sx, int sy, int N, array< double, 2 >^%mact, array< double, 2 >^%macout, int min_roznica/*,int remaining*/, ManualResetEvent ^%mre, int nextIteration, int r2, int exclusiveUpperBound)
	{
		this->sx = sx;
		this->sy = sy;
		this->N = N;
		this->mact = mact;
		this->macout = macout;
		this->min_roznica = min_roznica;
		/*this->remaining = remaining;*/
		this->mre = mre;
		this->nextIteration = nextIteration;
		this->r2 = r2;
		this->exclusiveUpperBound = exclusiveUpperBound;
	}

	TaskInfo(int sy, int N, array< double, 2 >^%mact, array< double, 2 >^%macout, int min_roznica, /*int remaining,*/ ManualResetEvent ^%mre, int nextIteration, int exclusiveUpperBound)
	{

		this->sy = sy;
		this->N = N;
		this->mact = mact;
		this->macout = macout;
		this->min_roznica = min_roznica;
		/*this->remaining = remaining;*/
		this->mre = mre;
		this->nextIteration = nextIteration;
		this->exclusiveUpperBound = exclusiveUpperBound;
	}



};




array< double, 2 >^ SDA::SDA_disc(array< double, 2 >^%mac, int sx, int sy, double r, int mode, int min_roznica)
{

	if (mac == nullptr || mac->Length != sx * sy)
		return mac;

	if (r < 1.0)
		r = 1.0;

	int N = (int)ceil(r);

	mode %= 6;


	array< double, 2 >^ macout = nullptr;
	array< double, 2 >^ mact = nullptr;

	if (macout == nullptr || macout->Length != sx * sy)
		macout = gcnew array<double, 2>(sx, sy);

	// CO TO JEST?

	Mac2MacMargUshort(mac, sx, sy, N, mact);
	if (mact == nullptr)
		return mac;


	int exclusiveUpperBound = sx;
	int inclusiveLowerBound = 0;

	int numProcs = Environment::ProcessorCount;

	if (numProcs > MaxCPU && MaxCPU > 0)
		numProcs = MaxCPU;
	if (numProcs < 1)
		numProcs = 1;

	int nextIteration = inclusiveLowerBound;

	remaining = numProcs;

	int r2 = (int)(r * r);

	if (mode == 0)
	{
		ManualResetEvent^ mre = gcnew ManualResetEvent(false);

		// Create each of the threads.
		for (int p = 0; p < numProcs; p++)
		{
			//dodac mre
			//czy to bedzie dzialalo? pamietac o tym zeby zmodyfikowac te wartosci
			TaskInfo^ ti = gcnew TaskInfo(sx, sy, N, mact, macout, min_roznica/*, remaining*/, mre, nextIteration, r2, exclusiveUpperBound);
			ThreadPool::QueueUserWorkItem(gcnew WaitCallback(ThreadProcMode0), ti);



			//);
		}
		// Wait for all threads to complete.
		mre->WaitOne();
		int i, j, mi, mj;


		/*while ((i = Interlocked::Increment(nextIteration) - 1) < (exclusiveUpperBound)) {


		for (j = 0; j < sy; j++)
		{

		macout[i, j] = 0;

		for (mi = -N; mi <= N; mi++)
		for (mj = -N; mj <= N; mj++)
		if (mi * mi + mj * mj <= r2)
		if (mact[i + mi + N, j + mj + N] >= mact[i + N, j + N] + min_roznica)
		macout[i, j]++;
		}
		}*/
	}


	if (mode == 1)
	{
		ManualResetEvent^ mre = gcnew ManualResetEvent(false);

		for (int p = 0; p < numProcs; p++)
		{

			TaskInfo^ ti = gcnew TaskInfo(sx, sy, N, mact, macout, min_roznica/*, remaining*/, mre, nextIteration, r2, exclusiveUpperBound);
			ThreadPool::QueueUserWorkItem(gcnew WaitCallback(ThreadProcMode0), ti);



			//);
		}
		// Wait for all threads to complete.
		mre->WaitOne();

	}

	//for (int i = 0; i < sx; ++i) {
	//

	//	for (int j = 0; j < sy; ++j) {

	//	
	//		std::cout << std::setw(5)<<macout[i,j];
	//		
	//	}
	//	std::cout << std::endl;
	//}



	return macout;
}








array< double, 2 >^ SDA::SDA_cross(array< double, 2 >^%mac, int sx, int sy, double r, int mode, int min_roznica)
{
	if (mac == nullptr || mac->Length != sx * sy)
		return mac;

	if (r < 1.0)
		r = 1.0;

	int N = (int)ceil(r);
	//int R = (int)((double)N * Math.Sqrt(2.0) / 2.0);

	mode %= 6;

	array< double, 2 >^macout = nullptr;

	if (macout == nullptr || macout->Length != sx * sy)
		macout = gcnew array<double, 2>(sx, sy);

	array< double, 2 >^mact = nullptr;


	Mac2MacMargUshort(mac, sx, sy, N, mact);
	if (mact == nullptr)
		return mac;


	int exclusiveUpperBound = sx;
	int inclusiveLowerBound = 0;

	int numProcs = Environment::ProcessorCount;

	if (numProcs > MaxCPU && MaxCPU > 0)
		numProcs = MaxCPU;
	if (numProcs < 1)
		numProcs = 1;

	int nextIteration = inclusiveLowerBound;

	int remaining = numProcs;

	if (mode == 0)
	{
		ManualResetEvent ^mre = gcnew ManualResetEvent(false);

		// Create each of the threads.
		for (int p = 0; p < numProcs; p++)
		{
			//dodac mre
			//czy to bedzie dzialalo? pamietac o tym zeby zmodyfikowac te wartosci
			TaskInfo^ ti = gcnew TaskInfo(sy, N, mact, macout, min_roznica/*, remaining*/, mre, nextIteration, exclusiveUpperBound);
			ThreadPool::QueueUserWorkItem(gcnew WaitCallback(ThreadProcCrossMod0), ti);
		}
		// Wait for all threads to complete.
		mre->WaitOne();

	}

	if (mode == 1)
	{
		ManualResetEvent ^mre = gcnew ManualResetEvent(false);

		// Create each of the threads.
		for (int p = 0; p < numProcs; p++)
		{
			//dodac mre
			//czy to bedzie dzialalo? pamietac o tym zeby zmodyfikowac te wartosci
			TaskInfo^ ti = gcnew TaskInfo(sy, N, mact, macout, min_roznica/*, remaining,*/, mre, nextIteration, exclusiveUpperBound);
			ThreadPool::QueueUserWorkItem(gcnew WaitCallback(ThreadProcCrossMod0), ti);
		}
		// Wait for all threads to complete.
		mre->WaitOne();

	}


	return macout;

}


void SDA::ThreadProcMode0(Object ^stateInfo)
{
	int i, j, mi, mj;
	TaskInfo^ ti = dynamic_cast<TaskInfo^>(stateInfo);

	while ((i = Interlocked::Increment(ti->nextIteration) - 1) < (ti->exclusiveUpperBound))
	{
		for (j = 0; j < ti->sy; j++)
		{
			ti->macout[i, j] = 0;

			for (mi = -ti->N; mi <= ti->N; mi++)
				for (mj = -ti->N; mj <= ti->N; mj++)
					if (mi * mi + mj * mj <= ti->r2)
						if (ti->mact[i + mi + ti->N, j + mj + ti->N] >= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
							ti->macout[i, j]++;
		}
	}

	if (Interlocked::Decrement(remaining) == 0) {

		ti->mre->Set();
	}

}

void SDA::ThreadProcMode1(Object ^stateInfo)
{
	int i, j, mi, mj;
	TaskInfo^ ti = dynamic_cast<TaskInfo^>(stateInfo);

	while ((i = Interlocked::Increment(ti->nextIteration) - 1) < (ti->exclusiveUpperBound))
		for (j = 0; j < ti->sy; j++)
		{
			ti->macout[i, j] = 0;

			for (mi = -ti->N; mi <= ti->N; mi++)
				for (mj = -ti->N; mj <= ti->N; mj++)
					if (mi * mi + mj * mj <= ti->r2)
						if (ti->mact[i + mi + ti->N, j + mj + ti->N] <= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
							ti->macout[i, j]++;
		}
	if (Interlocked::Decrement(remaining) == 0)
		ti->mre->Set();
}

void SDA::ThreadProcCrossMod0(Object ^stateInfo)
{
	int i, j, m;//mi, mj,
	TaskInfo^ ti = dynamic_cast<TaskInfo^>(stateInfo);

	while ((i = Interlocked::Increment(ti->nextIteration) - 1) < (ti->exclusiveUpperBound))
		for (j = 0; j < ti->sy; j++)
		{
			ti->macout[i, j] = 0;

			// pion
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + ti->N, j + m + ti->N] >= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;
			//poziom
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j + ti->N] >= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;

			//skos
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j + m + ti->N] >= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;

			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j - m + ti->N] >= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;
		}

	if (Interlocked::Decrement(remaining) == 0)
		ti->mre->Set();
}


void SDA::ThreadProcCrossMod1(Object ^stateInfo)
{
	int i, j, m;//mi, mj,
	TaskInfo^ ti = dynamic_cast<TaskInfo^>(stateInfo);

	while ((i = Interlocked::Increment(ti->nextIteration) - 1) < (ti->exclusiveUpperBound))
		for (j = 0; j < ti->sy; j++)
		{
			ti->macout[i, j] = 0;

			// pion
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + ti->N, j + m + ti->N] <= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;
			//poziom
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j + ti->N] <= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;

			//skos
			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j + m + ti->N] <= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;

			for (m = -ti->N; m <= ti->N; m++)
				if (ti->mact[i + m + ti->N, j - m + ti->N] <= ti->mact[i + ti->N, j + ti->N] + ti->min_roznica)
					ti->macout[i, j]++;
		}

	if (Interlocked::Decrement(remaining) == 0)
		ti->mre->Set();
}


int SDA::Mac2MacMargUshort(array< double, 2 >^%macin, int sx, int sy, int Marg, array< double, 2 >^%macout)
{
	if (macin == nullptr)
		return 0;
	if (sx < 1 || sy < 1 || sy <= Marg * 1 || sx <= Marg * 1)
		return 0;

	int i, j, k;
	//int msize = (int)Math.Sqrt(maska.Length);
	//int N = (int)Math.Floor((float)msize / 2.0);

	macout = gcnew array<double, 2>(sx + Marg * 2, sy + Marg * 2);

	// kopiowanie czesci zasadniczej
	for (i = 0; i < sx; i++)
		for (j = 0; j < sy; j++)
			macout[i + Marg, j + Marg] = macin[i, j];

	// kopiowanie marginesow
	for (i = 0; i < sx; i++)
	{
		for (k = 0; k <= Marg; k++)
		{
			macout[i + Marg, Marg - k] = macin[i, k];
			macout[i + Marg, sy - 1 + Marg + k] = macin[i, sy - 1 - k];
		}
	}

	for (j = 0; j < sy; j++)
	{
		for (k = 0; k <= Marg; k++)
		{
			macout[Marg - k, j + Marg] = macin[k, j];
			macout[sx - 1 + Marg + k, j + Marg] = macin[sx - 1 - k, j];
		}
	}

	// kopiowanie naroznikow

	for (i = 0; i <= Marg; i++)
		for (j = 0; j <= Marg; j++)
		{
			macout[Marg - i, Marg - j] = macin[i, j];
			macout[sx - 1 + Marg + i, Marg - j] = macin[sx - 1 - i, j];
			macout[Marg - i, sy - 1 + Marg + j] = macin[i, sy - 1 - j];
			macout[sx - 1 + Marg + i, sy - 1 + Marg + j] = macin[sx - 1 - i, sy - 1 - j];
		}

	return 1;
}

