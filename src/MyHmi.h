/**
*** Your Copyright Lines
**/

#pragma once

#include <string>
#include <iostream>
#include <symbol/core.h>
#include <symbol/rpc.h>

namespace my_namespace {
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
		static constexpr auto Option1_Flag{'a'}; ///Example flags
		static constexpr auto Option2_Flag{'b'};

	public:
		/// Constructor / Initialization/ Destruction
		MyHmi();
		MyHmi(Params&&p);
		~MyHmi() override;

		void init(const std::string& programName, const std::string& programDescription) override;

	protected:
		/// Provides an opportunity to rewrite params before executing.
		void pass1(ParamPath&) override;

	private:

		bool mainHandler(const Params& p, std::ostream& os) override;
		bool cmd1(const Params&, std::ostream&); /// Command Handler

		FlagDef flagdefOption1();
		FlagDef flagdefOption2();
		ptr<Section> createSectionCmd1();

		bool m_o1_set{false};
		bool m_o2_set{false};

	};

}

namespace my_namespace {

	//template<typename T> using ptr = c::ptr;
	using std::string;
	using std::ostream;

	template<typename B>
	MyHmi<B>::MyHmi(): b(Params{
		    flagdefOption1(),
		    flagdefOption1()
		}) {

	}

	template<typename B>
	MyHmi<B>::MyHmi(Params&&p): b(move(p)) {
		add(flagdefOption1());
		add(flagdefOption1());
	}

	template<typename B>
	MyHmi<B>::~MyHmi() {
	}

	template<typename B>
	void MyHmi<B>::init(const string& programName, const string& programDescription) {
		b::init(programName, programDescription);
		/// Add a subcommand
		this->add(CmdDef{"Cmd1", "Command1."}, createSectionCmd1());
	}

	template<typename B>
	MyHmi<B>::FlagDef MyHmi<B>::flagdefOption1() {
		return FlagDef{Option1_Flag, "option1", true, true, "defaultO1", "Option1 Description."};
	}

	template<typename B>
	MyHmi<B>::FlagDef MyHmi<B>::flagdefOption2() {
		return FlagDef{Option2_Flag, "option2", true, true, "defaultO2", "Option2 Description."};
	}

	template<typename B>
	MyHmi<B>::ptr<typename MyHmi<B>::Section> MyHmi<B>::createSectionCmd1() {
		auto s=new Section(Params{});
		s->set_handler([&](const Params& p, ostream& os) -> bool { return cmd1(p, os); });
		return s;
	}

	template<typename B>
	bool MyHmi<B>::cmd1(const Params& p, std::ostream& os) { /// Command Handler
		os << "Command1 Handler!.\n";
		return true;
	}

	template<typename B>
	bool MyHmi<B>::mainHandler(const Params& p, ostream& os) {
		m_o1_set = p.is_set(Option1_Flag);
		m_o2_set = p.is_set(Option2_Flag);
		return true;
	}

	template<typename B>
	void MyHmi<B>::pass1(ParamPath& v) {
		b::pass1(v);
	}

	using MyHmiOffline = MyHmi<symbol::core::Hmi>;
	using MyHmiOnline = MyHmi<symbol::Hmi>;

}



