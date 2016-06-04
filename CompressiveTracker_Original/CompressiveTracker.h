/************************************************************************
* File:	CompressiveTracker.h
* Brief: C++ demo for paper: Kaihua Zhang, Lei Zhang, Ming-Hsuan Yang,"Real-Time Compressive Tracking," ECCV 2012.
* Version: 1.0
* Author: Yang Xian
* Email: yang_xian521@163.com
* Date:	2012/08/03
* History:
* Revised by Kaihua Zhang on 14/8/2012
* Email: zhkhua@gmail.com
* Homepage: http://www4.comp.polyu.edu.hk/~cskhzhang/
************************************************************************/

//����һ���Ƚϳ��õ�C/C++��ע��ֻҪ��ͷ�ļ����ʼ����������ע�����ܹ���֤ͷ�ļ�ֻ������ͱ���һ�� 
#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace cv;
//---------------------------------------------------
class CompressiveTracker
{
public:
	CompressiveTracker(void);
	~CompressiveTracker(void);

private:

	int featureMinNumRect;
	int featureMaxNumRect;
	int featureNum;	//ÿ��box��harr����������Ҳ������������������
	vector<vector<Rect>> features;
	vector<vector<float>> featuresWeight;
	int rOuterPositive;	//������һ֡���ٵ���Ŀ��λ�õľ���С��rOuterPositive�ķ�Χ�ڲɼ� ������
	vector<Rect> samplePositiveBox;		//�ɼ���������box��
	vector<Rect> sampleNegativeBox;		//�ɼ��ĸ�����box��
	int rSearchWindow;		//ɨ�贰�ڵĴ�С������˵���box�Ĵ�С
	Mat imageIntegral;		//ͼ��Ļ���ͼ
	Mat samplePositiveFeatureValue;		//�ɼ�����������harr����ֵ
	Mat sampleNegativeFeatureValue;		//�ɼ��ĸ�������harr����ֵ

	//��ÿ������z��mά�����������ĵ�ά��ʾ��v��nά������nԶС��m�����ٶ�v�еĸ�Ԫ���Ƕ����ֲ��ġ�  
	//�ٶ��ڷ�����H(v)�е���������p(vi|y=1)��p(vi|y=0)���ڸ�˹�ֲ������ҿ����������ĸ�������������  
	//�ֱ����������������ĸ�˹�ֲ��ľ�ֵu�ͷ���sigma
	vector<float> muPositive;		//�������ľ�ֵ	
	vector<float> sigmaPositive;	//�������ķ���
	vector<float> muNegative;		//�������ľ�ֵ
	vector<float> sigmaNegative;	//�������ķ���
	float learnRate;		//ѧϰ���ʣ����Ʒ������������µĲ���
	vector<Rect> detectBox;		//��Ҫ����box
	Mat detectFeatureValue;
	RNG rng;		//�����

private:
	void HaarFeature(Rect& _objectBox, int _numFeature);
	void sampleRect(Mat& _image, Rect& _objectBox, float _rInner, float _rOuter, int _maxSampleNum, vector<Rect>& _sampleBox);
	void sampleRect(Mat& _image, Rect& _objectBox, float _srw, vector<Rect>& _sampleBox);
	void getFeatureValue(Mat& _imageIntegral, vector<Rect>& _sampleBox, Mat& _sampleFeatureValue);
	void classifierUpdate(Mat& _sampleFeatureValue, vector<float>& _mu, vector<float>& _sigma, float _learnRate);
	void radioClassifier(vector<float>& _muPos, vector<float>& _sigmaPos, vector<float>& _muNeg, vector<float>& _sigmaNeg,
		Mat& _sampleFeatureValue, float& _radioMax, int& _radioMaxIndex);
public:
	void processFrame(Mat& _frame, Rect& _objectBox);
	void init(Mat& _frame, Rect& _objectBox);
};
