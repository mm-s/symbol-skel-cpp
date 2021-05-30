/**
*** Your Copyright Lines
**/

#pragma once
#include <symbol/core.h>

namespace my_offline_project {
	///Each layer of speciaslisation of the Hmi class provide added function/features

	/// Human-Machine Interface. All sections command processor (offline)
	class MyHmi: public symbol::core::HMINode {

		///User Flags definition
		static constexpr auto Output_Flag{'o'}; ///Users specifying the output format.
		static constexpr auto Network_Flag{'n'};  ///User specifying the network type.

	/// Write your specialisation...
	protected:
		void rewrite(ParamsPath& p) const override; /// Opportunity to rewrite params.

		void init(const string& nm, const string& dc) override {
			set_handler([&](const Params& p, ostream& os) -> bool { return main_handler(p, os); });
		}

	private:

	bool main_handler(const Params& p, ostream& os) {
		n_overriden=p.is_set(Network_Flag);
		net::type_t t=net::type_from_name(p.get(Network_Flag));
		delete n;
		n=new symbol::net(t);
		if (!n->is_valid_type()) {
		    os << "Network type '" << p.get(Network_Flag) << "' is invalid.";
		    return false;
		}
		json=p.get(Output_Flag)=="json";
		hide_labels=p.is_set(HideLabels_Flag);
		return true;
	}


	};

}}
