#include "stdbool.h"
#include "standard_calc.h"

/**
 * @brief Bounds the provided angle between [-180, 180) degrees.
 *
 * e.g.)
 *      bound_to_180(135) = 135.0
 *      bound_to_180(200) = -160.0
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The bounded angle in degrees.
 */
float bound_to_180(float angle) {
    float result = angle;
    
    while(result < -180.0){ //inclusive i.e -600.0
        result = result + 360.0;
    }
    while(result >= 180.0){//exclusive i.e 400.0
        result = result - 360.0;
    }
    return result;
}

/**
 * @brief Determines whether an angle is between two other angles
 *
 *  e.g.)
 *      is_angle_between(0, 45, 90) = true
 *      is_angle_between(45, 90, 270) = false
 * 
 * @param first_angle:  The first bounding angle in degrees.
 * @param middle_angle: The angle in question in degrees.
 * @param second_angle: The second bounding angle in degrees.
 * @return bool: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`, FALSE otherwise
 */

//Purpose had to google: Is the middle angle between the smallest arc between first and second angle
//for second case smallest arc is 135 and 90 is not between that is angle middle in the range of acute angle spanned by both angles
bool is_angle_between(float first_angle, float middle_angle, float second_angle) {
    //step.1 normalize angles
    float second = bound_to_180(second_angle);
    float first = bound_to_180(first_angle);
    float middle = bound_to_180(middle_angle);

    //step.2 find the difference between the bounds
    float difference = bound_to_180(second - first); //test case = -135.0 this step finds that acute angle between second/first 
    //the above spans from first to second
    float first_mid_diff = bound_to_180(middle - first); //spans from first to middle second case 45 CW

    //step.3 determine if value falls in difference
    //had to google a positive difference = counter clockwise, negative = clockwise
    if(difference >= 0){ //CCW is the fastest arc
        //had to chat this part, if first -> middle is also CCW and doesnt overshoot first-> second we can return true
        if(first_mid_diff >= 0 && first_mid_diff <= difference){
            return true;
        }
        else return false;
    }
    else{//difference < 0 so CW
        //if also CW and doesnt overshoot return true
        if(first_mid_diff < 0 && first_mid_diff > difference){ //must be greater compare -120 and -135 if greater then within bounds
            return true;
        }
        else return false;
    }
}
