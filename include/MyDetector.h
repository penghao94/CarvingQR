#pragma once
#include<zxing/qrcode/detector/Detector.h>
namespace zxing {
	class DecodeHints;
	namespace qrcode{
		class MyDetector :public Detector {
		private:
			Ref<BitMatrix>image;
		public:
			MyDetector(Ref<BitMatrix>img) :Detector(img) { image = img; }
			std::pair<std::vector<std::vector<int>>, Ref<BitMatrix>>processFinderPatternInfo(DecodeHints const&hints);
			
		};
	}
}