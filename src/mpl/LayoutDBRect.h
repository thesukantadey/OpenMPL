/*************************************************************************
    > File Name: LayoutDBRect.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sat 29 Aug 2015 11:47:20 AM CDT
 ************************************************************************/

#ifndef SIMPLEMPL_LAYOUTDBRECT_H
#define SIMPLEMPL_LAYOUTDBRECT_H

#include "LayoutDB.h"

SIMPLEMPL_BEGIN_NAMESPACE

/// =====================================================================
/// LayoutDBRect enables rectangle-only layout with high memory and time 
/// efficiency. I try to only keep minimum volumn of data without much 
/// performance overhead. Only one copy of rectangles are allocated and 
/// their pointers are used in vector array and rtree. 
/// =====================================================================

/// current implementation assume all the input patterns are rectangles 
struct LayoutDBRect : public LayoutDB
{
    typedef LayoutDB base_type;
	typedef base_type::coordinate_type coordinate_type;

	LayoutDBRect();
	LayoutDBRect(coordinate_type xl, coordinate_type yl, coordinate_type xh, coordinate_type yh);
	LayoutDBRect(LayoutDBRect const& rhs);
	virtual ~LayoutDBRect();
	LayoutDBRect& operator=(LayoutDBRect const& rhs);

	void copy(LayoutDBRect const& rhs);
	virtual void add_pattern(int32_t layer, std::vector<point_type> const& vPoint);
	/// call it to initialize rtree 
	/// it should be faster than gradually insertion 
	virtual void initialize_data();
    /// \return poly rect patterns 
    virtual std::vector<rectangle_pointer_type> const& polyrect_patterns() const {return vPatternBbox;}
    /// set color for patterns 
    /// \param pattern_id is the index of vPatternBbox
    virtual void set_color(uint32_t pattern_id, int8_t color);
    /// mainly used for outputing edges 
    /// \return a point that is on the pattern and close to its center with given pattern id (polygon id for LayoutDBPolygon)
    /// default is to return the center of rectangle in vPatternBbox
    virtual point_type get_point_closest_to_center(uint32_t pattern_id) const; 
	virtual void report_data() const;

    /// \return the euclidean distance of two patterns 
    virtual coordinate_difference euclidean_distance(rectangle_type const& r1, rectangle_type const& r2) const {return gtl::euclidean_distance(r1, r2);}

    /// always return false as each rectangle is its own parent 
    //virtual bool same_parent(uint32_t, uint32_t) const {return false;}
};

SIMPLEMPL_END_NAMESPACE

#endif
