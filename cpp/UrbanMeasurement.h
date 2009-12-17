/**
 * @file    UrbanMeasurement.h
 * @brief   A Nonlinear Factor, specialized for Urban application
 * @author  Frank Dellaert
 * @author  Viorela Ila
 */

#pragma once

#include "NonlinearFactor.h"
#include "GaussianFactor.h"
#include "Testable.h"
#include "Point2.h"

namespace gtsam {

class UrbanConfig;

/**
 * Non-linear factor for a constraint derived from a 2D measurement,
 */
class UrbanMeasurement : public NonlinearFactor<UrbanConfig>, Testable<UrbanMeasurement>
{
private:

	int robotPoseNumber_, landmarkNumber_;
	std::string robotPoseName_, landmarkName_;
	//boost::shared_ptr<Cal3_S2> K_; // Calibration stored in each factor. FD: need to think about this.
	typedef NonlinearFactor<UrbanConfig> ConvenientFactor;

public:

	typedef boost::shared_ptr<UrbanMeasurement> shared_ptr; // shorthand for a smart pointer to a factor
	//typedef boost::shared_ptr<Cal3_S2> shared_ptrK;

	/**
	 * Default constructor
	 */
	UrbanMeasurement();

	/**
	 * Constructor
	 * @param z is the 2 dimensional location of landmark respect to the robot (the measurement)
	 * @param sigma is the standard deviation
	 * @param robotPoseNumber is basically the pose number
	 * @param landmarkNumber is the index of the landmark
	 *
	 *
	 */
	UrbanMeasurement(const Point2& z, double sigma, int robotPoseNumber, int landmarkNumber);


	/**
	 * print
	 * @param s optional string naming the factor
	 */
	void print(const std::string& s="UrbanMeasurement") const;

	/**
	 * equals
	 */
	bool equals(const UrbanMeasurement&, double tol=1e-9) const;

	/**
	 * predict the measurement (is that update ??)
	 */
	Vector predict(const UrbanConfig&) const;

	/**
	 * calculate the error of the factor
	 */
	Vector error_vector(const UrbanConfig&) const;

	/**
	 * linerarization
	 */

	GaussianFactor::shared_ptr linearize(const UrbanConfig&) const {
		//TODO implement linearize

	};

	int getrobotPoseNumber() const { return robotPoseNumber_; }
	int getLandmarkNumber()    const { return landmarkNumber_;    }



private:
	/** Serialization function */
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & BOOST_SERIALIZATION_NVP(robotPoseNumber_);
		ar & BOOST_SERIALIZATION_NVP(landmarkNumber_);
		ar & BOOST_SERIALIZATION_NVP(robotPoseName_);
		ar & BOOST_SERIALIZATION_NVP(landmarkName_);
	}
};

}
