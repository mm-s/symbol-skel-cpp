/**
*** Your Copyright Lines
**/
#include "Hmi.h"

namespace my_namespace {

	using c = Hmi;

	c::Hmi(): b(Params{
		    flagdef_output(),
		    flagdef_hide_labels(),
		    flagdef_network(),
		}) {

	}

	c::Hmi(Params&&p): b(move(p)) {
		add(flagdef_output());
		add(flagdef_hide_labels());
		add(flagdef_network());
	}

	c::~Hmi() {
		delete n;
	}

	void c::init(const string& nm, const string& dc) {
		b::init(nm, dc);
		set_handler([&](const Params& p, ostream& os) -> bool { return main_handler(p, os); });
	}

	c::FlagDef c::flagdef_network() {
		ostringstream n;
		n << "Network type. Value in (";
		symbol::net::list(n);
		n << ").";
		return FlagDef{Network_Flag, "network", true, true, "public-test", n.str()};
	}

	c::FlagDef c::flagdef_output() {
		return FlagDef{Output_Flag, "output", true, true, "text", "Output format. Value in (text json)"};
	}

	c::FlagDef c::flagdef_hide_labels() {
		return FlagDef{HideLabels_Flag, "hide-labels", true, false, "", "Hide field names. (Only on text output mode)"};
	}

	bool c::main_handler(const Params& p, ostream& os) {
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

	void c::rewrite(v_t& v) const {
		auto p=v.lookup({"tx", "transfer"});
		if (p!=nullptr) {
		    auto r=v.lookup({});
		    //assert(r->has(Seed_Flag));
		    //r->set_mandatory(Seed_Flag);
		}
	}

}}
