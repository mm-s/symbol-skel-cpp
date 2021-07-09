/**
*** Your Copyright Lines
**/

#pragma once

#include <string>
#include <iostream>
#include <symbol/core.h>
#include <symbol/rpc.h>

namespace my_namespace {
	using std::ostream;
	using std::string;
	///Each layer of speciaslisation of the Hmi class provide added function/features

	/// Human-Machine Interface. All sections command processor (offline)
	template<typename B>
	class MyHmi: public B {
		/// base class is b
		using b = B; //symbol::core::Hmi;
	public:
		using Params = typename b::Params;
		using ParamPath = typename b::ParamPath;
		using FlagDef = typename b::FlagDef;
		using CmdDef = typename b::CmdDef;
		using Section = typename b::Section;
		template<typename T> using ptr = symbol::ptr<T>;
	public:
		///User Flags definition
		static constexpr auto Option1_Flag{'Z'}; ///Example flags
		static constexpr auto Option2_Flag{'z'};
		static constexpr auto Option3_Flag{'X'};
		static constexpr auto Option4_Flag{'Y'};

	public:
		/// Constructor / Initialization/ Destruction
		MyHmi();
		MyHmi(Params&&p);
		~MyHmi() override;

		void init(const std::string& programName, const std::string& programDescription) override;

	protected:
		/// Provides an opportunity to rewrite params before executing.
		bool pass1(ParamPath&, ostream&) override;
		void help_flag(const FlagDef&, ostream&) const override;

	private:
		static Params defParams();
		static Params defCmd1Params();

		virtual bool main(Params&, bool last, ostream&) override;
		bool cmd1(Params&, bool last, std::ostream&); /// Command Handler

		ptr<Section> createSectionCmd1();

		bool m_o1_set{false};
		bool m_o2_set{false};
		bool m_o3_set{false};
		string m_o4;

	};

}

namespace my_namespace {

	//template<typename T> using ptr = c::ptr;
	using std::string;
	using std::ostream;

	template<typename B>
	MyHmi<B>::MyHmi(): b(defParams()) {
	}


	template<typename B>
	MyHmi<B>::MyHmi(Params&&p): b(move(p)) {
		add(defParams()); //params at global scope
	}

	template<typename B>
	MyHmi<B>::~MyHmi() {
	}

	template<typename B>
	MyHmi<B>::Params MyHmi<B>::defParams() {
		return Params{	//             optional
						//                   requires input
			{Option1_Flag, "option1", true, false, "defaultO1", "Global Option1 Description."},
			{Option2_Flag, "option2", true, false, "defaultO2", "Global Option2 Description."}
		};
	}

	template<typename B>
	MyHmi<B>::Params MyHmi<B>::defCmd1Params() {
		return Params{
			{Option3_Flag, "option3", true, false, "defaultO3", "Cmd1 Option3 Description."},
			{Option4_Flag, "option4", true, true, "defaultO4", "Cmd1 Option4 Description."}
		};
	}

	template<typename B>
	void MyHmi<B>::help_flag(const FlagDef& f, ostream& os) const {
		if (f.short_name == Option1_Flag) {
			os << "Help for flag1'\n'";
			return;
		}
		else if (f.short_name == Option2_Flag) {
			os << "Help for flag2'\n'";
			return;
		}
		else if (f.short_name == Option3_Flag) {
			os << "Help for flag3'\n'";
			return;
		}
		else if (f.short_name == Option4_Flag) {
			os << "Help for flag4'\n'";
			return;
		}
		b::help_flag(f, os);
	}

	template<typename B>
	void MyHmi<B>::init(const string& programName, const string& programDescription) {
		b::init(programName, programDescription);
		/// Add a subcommand
		this->add(CmdDef{"Cmd1", "Command1."}, createSectionCmd1());
	}

	template<typename B>
	MyHmi<B>::ptr<typename MyHmi<B>::Section> MyHmi<B>::createSectionCmd1() {
		auto s=new Section(defCmd1Params()); //params at Cmd1 scope
		s->set_handler([&](Params& p, bool last, ostream& os) -> bool { return cmd1(p, last, os); });
		return s;
	}

	template<typename B>
	bool MyHmi<B>::cmd1(Params& p, bool last, std::ostream& os) { /// Command Handler
		m_o3_set = p.is_set(Option3_Flag);
		m_o4 = p.get(Option4_Flag);
		if (last) {
			os << "Command1 Handler!.\n";
		}
		else {
			//no output on screen, there are further handlers
		}
		return true;
	}

	template<typename B>
	bool MyHmi<B>::main(Params& p, bool last, ostream& os) {
		if (!b::mainHandler(p, last, os)) return false;
		m_o1_set = p.is_set(Option1_Flag);
		m_o2_set = p.is_set(Option2_Flag);
		return true;
	}

	template<typename B>
	bool MyHmi<B>::pass1(ParamPath& v, ostream& os) {
		return b::pass1(v, os);
	}

	using MyHmiOffline = MyHmi<symbol::core::Hmi>;
	using MyHmiOnline = MyHmi<symbol::Hmi>;

}



