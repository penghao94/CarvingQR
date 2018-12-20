#include "pixelVisibility.h"
// Define the used kernel and arrangement  
typedef CGAL::Exact_predicates_exact_constructions_kernel       Kernel;
typedef Kernel::FT												FT;
typedef Kernel::Point_2											Point_2;
typedef Kernel::Segment_2                                       Segment_2;
typedef CGAL::Arr_segment_traits_2<Kernel>                      Traits_2;
typedef CGAL::Arrangement_2<Traits_2>                           Arrangement_2;
typedef Arrangement_2::Halfedge_const_handle                    Halfedge_const_handle;
typedef Arrangement_2::Face_handle                              Face_handle;
// Define the used visibility class 
typedef CGAL::Triangular_expansion_visibility_2<Arrangement_2, CGAL::Tag_true>  TEV;

 std::vector<cv::Point> conn::pixelVisibility(cv::Point &queryPixel,std::vector<cv::Point>contour){
	 std::vector<cv::Point> visibleContour;
	 
	 std::vector<Segment_2> segments;
	for (int i = 0; i <contour.size(); i++) {
		Point_2 s(static_cast<double>(contour[i].x),static_cast<double>(contour[i].y));
		Point_2 d(static_cast<double>(contour[(i+1)%contour.size()].x),static_cast<double>(contour[(i+1)%contour.size()].y));;
		
		segments.push_back(Segment_2(s, d));
	}
	//Defining the query point
	Point_2 q(static_cast<double> (queryPixel.x), static_cast<double> (queryPixel.y));
	// insert geometry into the arrangement 
	Arrangement_2 env;
	CGAL::insert_non_intersecting_curves(env, segments.begin(), segments.end());

	//Find the halfedge whose target is the query point.
	//(usually you may know that already by other means)  
	Face_handle fit;
	for (fit = env.faces_begin(); fit != env.faces_end(); ++fit) {
		if (!fit->is_unbounded()) {
			break;
			std::cout << "Holy shit" << std::endl;
		}
	}
	//visibility query
	Arrangement_2 output_arr;
	TEV tev(env);
	Face_handle fh = tev.compute_visibility(q, fit, output_arr);
	Arrangement_2::Ccb_halfedge_circulator curr = fh->outer_ccb();

	visibleContour.emplace_back(static_cast<int>(CGAL::to_double(curr->source()->point().x())), static_cast<int>(CGAL::to_double(curr->source()->point().y())));
	while (++curr != fh->outer_ccb()) {
		visibleContour.emplace_back(static_cast<int>(CGAL::to_double(curr->source()->point().x())), static_cast<int>(CGAL::to_double(curr->source()->point().y())));
	}

	return visibleContour;
 }
