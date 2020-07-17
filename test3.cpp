#include<iostream>
#include<string>


using namespace std;

class RISCV {
public:
	string memory;
	unsigned int* x;
	int pc;
	int jumpPredictor;
	bool flag_IF, flag_ID, flag_EX, flag_MEM, flag_WB;
	bool endTag;
	enum instructionType {
		LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU,
		LB, LH, LW, LBU, LHU, SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI,
		SRAI, ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND, END
	};
	enum instructionType iType_IF, iType_ID, iType_EX, iType_MEM, iType_WB, iType_IF_ID, iType_ID_EX, iType_EX_MEM, iType_MEM_WB;

	int pc_value_IF;
	unsigned int pcRegister_value_IF;

	int rs1_ID, rs2_ID, rd_ID, offset_ID, immediate_ID, pc_value_ID;
	unsigned int rs1_value_u_ID, rs2_value_u_ID, rd_value_u_ID;
	bool shiftFlag_ID;
	unsigned int pcRegister_value_ID;

	int rs1_EX, rs2_EX, rd_EX, offset_EX, immediate_EX, pc_value_EX, rd_value_EX;
	unsigned int rs1_value_u_EX, rs2_value_u_EX, rd_value_u_EX, lsaddress_EX;
	bool shiftFlag_EX;

	int rs2_MEM, rd_MEM, pc_value_MEM;
	unsigned int lsaddress_MEM, rd_value_u_MEM;
	bool shiftFlag_MEM;

	int rd_WB;
	unsigned int rd_value_u_WB;
	bool shiftFlag_WB;


	int pc_value_IF_ID;
	unsigned int pcRegister_value_IF_ID;

	int rs1_ID_EX, rs2_ID_EX, rd_ID_EX, offset_ID_EX, immediate_ID_EX, pc_value_ID_EX;
	unsigned int rs1_value_u_ID_EX, rs2_value_u_ID_EX, rd_value_u_ID_EX;
	int shiftFlag_ID_EX;

	int rs2_EX_MEM, rd_EX_MEM, pc_value_EX_MEM;
	unsigned int lsaddress_EX_MEM, rd_value_u_EX_MEM;
	int shiftFlag_EX_MEM;

	int rd_MEM_WB, shiftFlag_MEM_WB;
	unsigned int rd_value_u_MEM_WB;



	RISCV();
	~RISCV();

	void IFConvertToID();
	void IDConvertToEX();
	void EXConvertToMEM();
	void MEMConvertToWB();

	void IDGetFromIF();
	void EXGetFromID();
	void MEMGetFromEX();
	void WBGetFromMEM();

	void testOutput_IF();
	void testOutput_ID();
	void testOutput_EX();
	void testOutput_MEM();
	void testOutput_WB();
	void readFile();
	void run();
	void IF();
	void ID();
	void EX();
	void MEM();
	void WB();
	void forwarding();
	void forwarding1();
	void forwarding2();
	void NumberToHex(int num, char& result);
	unsigned int HexToNumber(char& num);
};
RISCV::RISCV()
{
	memory.assign(400000, '0');
	pc = 0;
	x = new unsigned int[32];
	for (int i = 0; i < 32; ++i) x[i] = 0;

	jumpPredictor = 0;
	flag_IF = true;
	flag_ID = flag_EX = flag_MEM = flag_WB = false;
	endTag = false;

}

RISCV::~RISCV()
{
	delete[] x;
}

void RISCV::IFConvertToID()
{
	pc_value_IF_ID = pc_value_IF;
	pcRegister_value_IF_ID = pcRegister_value_IF;

	iType_IF_ID = iType_IF;

	flag_ID = flag_IF;
}

void RISCV::IDConvertToEX()
{
	rs1_ID_EX = rs1_ID;
	rs2_ID_EX = rs2_ID;
	rd_ID_EX = rd_ID;
	offset_ID_EX = offset_ID;
	immediate_ID_EX = immediate_ID;
	pc_value_ID_EX = pc_value_ID;
	rs1_value_u_ID_EX = rs1_value_u_ID;
	rs2_value_u_ID_EX = rs2_value_u_ID;
	rd_value_u_ID_EX = rd_value_u_ID;
	shiftFlag_ID_EX = shiftFlag_ID;

	iType_ID_EX = iType_ID;

	flag_EX = flag_ID;

}

void RISCV::EXConvertToMEM()
{
	rs2_EX_MEM = rs2_EX;
	rd_EX_MEM = rd_EX;
	pc_value_EX_MEM = pc_value_EX;
	lsaddress_EX_MEM = lsaddress_EX;
	shiftFlag_EX_MEM = shiftFlag_EX;

	rd_value_u_EX_MEM = rd_value_u_EX;

	iType_EX_MEM = iType_EX;

	flag_MEM = flag_EX;

}

void RISCV::MEMConvertToWB()
{
	rd_MEM_WB = rd_MEM;
	shiftFlag_MEM_WB = shiftFlag_MEM;

	rd_value_u_MEM_WB = rd_value_u_MEM;

	iType_MEM_WB = iType_MEM;

	flag_WB = flag_MEM;
}

void RISCV::IDGetFromIF()
{
	pc_value_ID = pc_value_IF_ID;
	pcRegister_value_ID = pcRegister_value_IF_ID;

	iType_ID = iType_IF_ID;
}

void RISCV::EXGetFromID()
{
	rs1_EX = rs1_ID_EX;
	rs2_EX = rs2_ID_EX;
	rd_EX = rd_ID_EX;
	offset_EX = offset_ID_EX;
	immediate_EX = immediate_ID_EX;
	pc_value_EX = pc_value_ID_EX;
	rs1_value_u_EX = rs1_value_u_ID_EX;
	rs2_value_u_EX = rs2_value_u_ID_EX;
	rd_value_u_EX = rd_value_u_ID_EX;
	shiftFlag_EX = shiftFlag_ID_EX;


	iType_EX = iType_ID_EX;
}

void RISCV::MEMGetFromEX()
{
	rs2_MEM = rs2_EX_MEM;
	rd_MEM = rd_EX_MEM;
	pc_value_MEM = pc_value_EX_MEM;
	lsaddress_MEM = lsaddress_EX_MEM;
	shiftFlag_MEM = shiftFlag_EX_MEM;

	rd_value_u_MEM = rd_value_u_EX_MEM;
	iType_MEM = iType_EX_MEM;
}

void RISCV::WBGetFromMEM()
{
	rd_WB = rd_MEM_WB;
	shiftFlag_WB = shiftFlag_MEM_WB;

	rd_value_u_WB = rd_value_u_MEM_WB;

	iType_WB = iType_MEM_WB;
}

void RISCV::readFile()
{
	string s;
	string* str;
	str = new string[10];
	int pieces = -1;
	int* headAddress;
	headAddress = new int[10];
	for (int i = 0; i < 10; ++i) headAddress[i] = 0;

	while (cin >> s)
	{
		if (s[0] == '@') {
			++pieces;
			int tmp = 1;
			for (int j = 8; j >= 5; --j) {
				if (s[j] <= '9') headAddress[pieces] += (s[j] - '0') * tmp;
				else headAddress[pieces] += (s[j] - 'A' + 10) * tmp;
				tmp *= 16;
			}
		}

		else str[pieces] = str[pieces] + s;
	}

	for (int i = 0; i <= pieces; ++i)
		memory.insert(headAddress[i] * 2, str[i]);

	delete[] str;
	delete[] headAddress;
}


void RISCV::run()
{
	bool preStop = false;
	int predictTime = 0, predictSuccess = 0;

	while (true) {

		WB();
		MEM();
		EX();
		ID();
		IF();

		forwarding();

		if (flag_MEM && flag_EX) {

			switch (iType_EX_MEM) {
			case LB:case LH:case LW:case LBU:case LHU:
			{
				if (rd_EX_MEM == rs1_ID_EX || rd_EX_MEM == rs2_ID_EX) {
					WB();
					MEM();
					forwarding();

				}
			}
			}


		}

		if (flag_EX) {
			switch (iType_ID_EX) {
			case JAL: {
				pc = pc_value_ID_EX + offset_ID_EX;
				flag_ID = false;
				break;
			}
			case JALR: {
				pc = (rs1_value_u_ID_EX + offset_ID_EX) & ~1;
				flag_ID = false;
				break;
			}
			case BEQ: case BNE: case BLT: case BGE: case BLTU: case BGEU:
			{
				if (jumpPredictor > 1) pc = pc_value_ID_EX + offset_ID_EX;
				else pc = pc_value_ID_EX + 4;
				flag_ID = false;
				/*++predictTime;*/
				break;
			}
			}
		}

		if (flag_MEM) {
			switch (iType_EX_MEM) {
			case BEQ: case BNE: case BLT: case BGE: case BLTU: case BGEU:
			{
				if (pc_value_EX_MEM == pc - 4) {
					flag_EX = flag_MEM = false;
					/*++predictSuccess; */
					break;
				}
				else {
					jumpPredictor = (jumpPredictor + 1) % 4;
					WB();
					MEM();
					flag_ID = flag_EX = flag_MEM = false;
					break;
				}
			}
			}
		}


		if (endTag) {
			/*cout << predictSuccess << " " << predictTime << " " << (double)predictSuccess / predictTime << endl;*/

			cout << (x[10] & 255);
			break;
		}


	}


}

//五级流水


void RISCV::IF()
{
	if (flag_IF) {
		pcRegister_value_IF = 0;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 2; ++j)
				pcRegister_value_IF += (HexToNumber(memory[2 * pc + 2 * i + j]) << (8 * i - 4 * j + 4));
		

		pc_value_IF = pc;
		pc += 4;

		
		switch ((pcRegister_value_IF & 127)) {
		case 55: iType_IF = LUI; break;
		case 23: iType_IF = AUIPC; break;
		case 111: iType_IF = JAL; break;
		case 103: iType_IF = JALR; break;
		case 99:
			switch ((pcRegister_value_IF >> 12) & 7) {
			case 0: iType_IF = BEQ; break;
			case 1: iType_IF = BNE; break;
			case 4: iType_IF = BLT; break;
			case 5: iType_IF = BGE; break;
			case 6: iType_IF = BLTU; break;
			case 7: iType_IF = BGEU; break;
			}break;
		case 3:
			switch ((pcRegister_value_IF >> 12) & 7) {
			case 0: iType_IF = LB; break;
			case 1: iType_IF = LH; break;
			case 2: iType_IF = LW; break;
			case 4: iType_IF = LBU; break;
			case 5: iType_IF = LHU; break;
			}break;
		case 35:
			switch ((pcRegister_value_IF >> 12) & 7) {
			case 0: iType_IF = SB; break;
			case 1: iType_IF = SH; break;
			case 2: iType_IF = SW; break;
			}break;
		case 19:
			switch ((pcRegister_value_IF >> 12) & 7) {
			case 0: iType_IF = ADDI; break;
			case 2: iType_IF = SLTI; break;
			case 3: iType_IF = SLTIU; break;
			case 4: iType_IF = XORI; break;
			case 6: iType_IF = ORI; break;
			case 7: iType_IF = ANDI; break;
			case 1: iType_IF = SLLI; break;
			case 5: 
				switch ((pcRegister_value_IF >> 30) & 1) {
				case 0: iType_IF = SRLI; break;
				case 1: iType_IF = SRAI; break;
				}break;
			}break;
		case 51:
			switch ((pcRegister_value_IF >> 12) & 7) {
			case 0: 
				switch ((pcRegister_value_IF >> 30) & 1) {
				case 0: iType_IF = ADD; break;
				case 1: iType_IF = SUB; break;
				}break;
			case 1: iType_IF = SLL; break;
			case 2: iType_IF = SLT; break;
			case 3: iType_IF = SLTU; break;
			case 4: iType_IF = XOR; break;
			case 5: 
				switch ((pcRegister_value_IF >> 30) & 1) {
				case 0: iType_IF = SRL; break;
				case 1: iType_IF = SRA; break;
				}break;
			case 6: iType_IF = OR; break;
			case 7: iType_IF = AND; break;
			}break;
		}

		if (pcRegister_value_IF == 267388179) iType_IF = END;

		/*testOutput_IF();*/
		IFConvertToID();

	}
}

void RISCV::ID()
{
	if (flag_ID) {

		IDGetFromIF();

		switch (iType_ID) {
		case END:flag_IF = false;

		case LUI: case AUIPC: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			immediate_ID = (pcRegister_value_ID >> 12) << 12;
			break;

		}

		case JAL: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			offset_ID = 0;
			offset_ID += ((pcRegister_value_ID >> 21)  & 1023) << 1;
			offset_ID += ((pcRegister_value_ID >> 12) & 255) << 12;
			offset_ID += ((pcRegister_value_ID >> 20) & 1) << 11;
			offset_ID += (int)(((pcRegister_value_ID >> 31) & 1) << 31) >> 11;

			break;
		}

		case JALR: case LB: case LH: case LW: case LBU: case LHU: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			offset_ID = 0;
			offset_ID += (pcRegister_value_ID >> 20) & 2047;
			offset_ID += (int)(((pcRegister_value_ID >> 31) & 1) << 31) >> 20;

			rs1_value_u_ID = x[rs1_ID];

			break;
		}

		case ADDI: case SLTI: case SLTIU: case XORI: case ORI: case ANDI: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			immediate_ID = 0;
			immediate_ID += (pcRegister_value_ID >> 20) & 2047;
			immediate_ID += (int)(((pcRegister_value_ID >> 31) & 1) << 31) >> 20;

			rs1_value_u_ID = x[rs1_ID];

			break;
		}



		case BEQ: case BNE: case BLT: case BGE: case BLTU: case BGEU: {
			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			rs2_ID = (pcRegister_value_ID >> 20) & 31;

			offset_ID = 0;
			offset_ID += ((pcRegister_value_ID >> 8) & 15) << 1;
			offset_ID += ((pcRegister_value_ID >> 25) & 63) << 5;
			offset_ID += ((pcRegister_value_ID >> 7) & 1) << 11;
			offset_ID += (int)(((pcRegister_value_ID >> 31) & 1) << 31) >> 19;

			rs1_value_u_ID = x[rs1_ID];
			rs2_value_u_ID = x[rs2_ID];

			break;
		}

		case SB: case SH: case SW: {
			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			rs2_ID = (pcRegister_value_ID >> 20) & 31;

			offset_ID = 0;
			offset_ID += ((pcRegister_value_ID >> 8) & 15) << 1;
			offset_ID += ((pcRegister_value_ID >> 25) & 63) << 5;
			offset_ID += (pcRegister_value_ID >> 7) & 1;
			offset_ID += (int)(((pcRegister_value_ID >> 31) & 1) << 31) >> 20;

			rs1_value_u_ID = x[rs1_ID];
			
			break;
		}

		case SLLI: case SRLI: case SRAI: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			shiftFlag_ID = !((pcRegister_value_ID >> 25) & 1);
			immediate_ID = (pcRegister_value_ID >> 20) & 63;

			rs1_value_u_ID = x[rs1_ID];
			break;
		}

		case ADD: case SUB:  case SLT: case SLTU: case XOR:  case OR: case AND: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			rs2_ID = (pcRegister_value_ID >> 20) & 31;

			rs1_value_u_ID = x[rs1_ID];
			rs2_value_u_ID = x[rs2_ID];

			break;
		}

		case SLL:case SRL: case SRA: {
			rd_ID = (pcRegister_value_ID >> 7) & 31;

			rs1_ID = (pcRegister_value_ID >> 15) & 31;

			rs2_ID = (pcRegister_value_ID >> 20) & 31;

			rs1_value_u_ID = x[rs1_ID];
			immediate_ID = x[rs2_ID] & 31;
			break;
		}

		}

		/*testOutput_ID();*/
		IDConvertToEX();
		flag_ID = false;
	}
}

void RISCV::forwarding1()
{
	//forwarding
	switch (iType_ID_EX) {
	case JALR: case LB: case LH: case LW: case LBU: case LHU:
	case ADDI:case SLTI:case SLTIU:case XORI:case ORI:case ANDI:
	case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
	case SB: case SH: case SW:case SLLI:case SRLI:case SRAI:case ADD:
	case SUB:case SLL:case SLT:case SLTU:case XOR:case SRL:case SRA:
	case OR:case AND:
		if (rs1_ID_EX == rd_MEM_WB && rd_MEM_WB != 0) {
			switch (iType_MEM_WB) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_MEM_WB) {
					rs1_value_u_ID_EX = rd_value_u_MEM_WB;
					/*cout << "forwarding1 1" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR: case LB:case LH:case LW:
			case LBU:case LHU:case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB: case SLL: case SLT: case SLTU: case XOR:
			case SRL: case SRA: case OR: case AND: {
				rs1_value_u_ID_EX = rd_value_u_MEM_WB;
				/*cout << "forwarding1 1" << endl << endl;*/
				break;
			}
			}
		}
	}

	switch (iType_ID_EX) {
	case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
	case ADD:case SUB:case SLT:case SLTU:case XOR:
	case OR:case AND:
		if (rs2_ID_EX == rd_MEM_WB && rd_MEM_WB != 0) {
			switch (iType_MEM_WB) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_MEM_WB) {
					rs2_value_u_ID_EX = rd_value_u_MEM_WB;
					/*cout << "forwarding1 2" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR: case LB:case LH:case LW:
			case LBU:case LHU:case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB:  case SLT: case SLTU: case XOR:
			case OR: case AND: case SLL:case SRL: case SRA: {
				rs2_value_u_ID_EX = rd_value_u_MEM_WB;
				/*cout << "forwarding1 2" << endl << endl;*/
				break;
			}
			}
		}break;

	case SLL:case SRL: case SRA: {
		if (rs2_ID_EX == rd_MEM_WB && rd_MEM_WB != 0) {
			switch (iType_MEM_WB) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_MEM_WB) {
					immediate_ID_EX = rd_value_u_MEM_WB & 31;
					/*cout << "forwarding1 2" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR: case LB:case LH:case LW:
			case LBU:case LHU:case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB:  case SLT: case SLTU: case XOR:
			case OR: case AND: case SLL:case SRL: case SRA: {
				immediate_ID_EX = rd_value_u_MEM_WB & 31;
				/*cout << "forwarding1 2" << endl << endl;*/
				break;
			}
			}
		}break;
	}

	}




}
void RISCV::forwarding2()
{
	switch (iType_ID_EX) {
	case JALR: case LB: case LH: case LW: case LBU: case LHU:
	case ADDI:case SLTI:case SLTIU:case XORI:case ORI:case ANDI:
	case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
	case SB: case SH: case SW:case SLLI:case SRLI:case SRAI:case ADD:
	case SUB:case SLL:case SLT:case SLTU:case XOR:case SRL:case SRA:
	case OR:case AND:
		if (rs1_ID_EX == rd_EX_MEM && rd_EX_MEM != 0) {
			switch (iType_EX_MEM) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_EX_MEM) {
					rs1_value_u_ID_EX = rd_value_u_EX_MEM;
					/*cout << "forwarding2 1" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR:case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB: case SLL: case SLT: case SLTU: case XOR:
			case SRL: case SRA: case OR: case AND: {
				rs1_value_u_ID_EX = rd_value_u_EX_MEM;
				/*cout << "forwarding2 1" << endl << endl;*/
				break;
			}
			}
		}
	}

	switch (iType_ID_EX) {
	case BEQ:case BNE:case BLT:case BGE:case BLTU:case BGEU:
	case ADD:case SUB:case SLT:case SLTU:case XOR:
	case OR:case AND:
		if (rs2_ID_EX == rd_EX_MEM && rd_EX_MEM != 0) {
			switch (iType_EX_MEM) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_EX_MEM) {
					rs2_value_u_ID_EX = rd_value_u_EX_MEM;
					/*cout << "forwarding2 2" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR: case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB:  case SLT: case SLTU: case XOR:
			case OR: case AND: case SLL:case SRL: case SRA: {
				rs2_value_u_ID_EX = rd_value_u_EX_MEM;
				/*cout << "forwarding2 2" << endl << endl;*/
				break;
			}
			}
		}break;

	case SLL:case SRL: case SRA: {
		if (rs2_ID_EX == rd_EX_MEM && rd_EX_MEM != 0) {
			switch (iType_EX_MEM) {
			case SLLI:case SRLI:case SRAI: {
				if (shiftFlag_EX_MEM) {
					immediate_ID_EX = rd_value_u_EX_MEM & 31;
					/*cout << "forwarding2 2" << endl << endl;*/
				}
				break;
			}
			case LUI: case AUIPC: case JAL: case JALR: case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
			case ANDI:case ADD: case SUB:  case SLT: case SLTU: case XOR:
			case OR: case AND: case SLL:case SRL: case SRA: {
				immediate_ID_EX = rd_value_u_EX_MEM & 31;
				/*cout << "forwarding2 2" << endl << endl;*/
				break;
			}
			}
		}break;
	}

	}

}
void RISCV::forwarding()
{
	if (flag_WB)
		forwarding1();

	if (flag_MEM)
		forwarding2();
}

void RISCV::EX()
{
	if (flag_EX) {

		EXGetFromID();

		switch (iType_EX) {

		case LUI: {
			rd_value_u_EX = immediate_EX;
			break;
		}

		case AUIPC: {
			rd_value_u_EX = immediate_EX + pc_value_EX;
			break;
		}

		case JAL: {
			rd_value_u_EX = pc_value_EX + 4;
			break;
		}


		case JALR: {
			rd_value_u_EX = pc_value_EX + 4;
			break;
		}

		case LB: case LH: case LW: case LBU: case LHU: {
			lsaddress_EX = rs1_value_u_EX + offset_EX;
			break;
		}

		case ADDI: {
			rd_value_u_EX = rs1_value_u_EX + immediate_EX;
			break;
		}

		case SLTI: {
			if ((int)rs1_value_u_EX < immediate_EX) rd_value_u_EX = 1;
			else rd_value_u_EX = 0;
			break;
		}

		case SLTIU: {
			if (rs1_value_u_EX < (unsigned int)immediate_EX) rd_value_u_EX = 1;
			else rd_value_u_EX = 0;
			break;
		}

		case XORI: {
			rd_value_u_EX = rs1_value_u_EX ^ immediate_EX;
			break;
		}

		case ORI: {
			rd_value_u_EX = rs1_value_u_EX | immediate_EX;
			break;
		}

		case ANDI: {
			rd_value_u_EX = rs1_value_u_EX & immediate_EX;
			break;
		}



		case BEQ: {
			if (rs1_value_u_EX == rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}



		case BNE: {
			if (rs1_value_u_EX != rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}

		case BLT: {
			if ((int)rs1_value_u_EX < (int)rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}

		case BGE: {
			if ((int)rs1_value_u_EX >= (int)rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}

		case BLTU: {
			if (rs1_value_u_EX < rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}

		case BGEU: {
			if (rs1_value_u_EX >= rs2_value_u_EX)
				pc_value_EX += offset_EX;
			else pc_value_EX += 4;
			break;
		}


		case SB: case SH: case SW: {
			lsaddress_EX = rs1_value_u_EX + offset_EX;
			break;
		}


		case SLLI: {
			if (shiftFlag_EX) {
				rd_value_u_EX = rs1_value_u_EX << immediate_EX;
			}
			break;
		}

		case SRLI: {
			if (shiftFlag_EX) {
				rd_value_u_EX = rs1_value_u_EX >> immediate_EX;
			}
			break;
		}

		case SRAI: {
			if (shiftFlag_EX) {
				rd_value_u_EX = (int)rs1_value_u_EX >> immediate_EX;
			}
			break;
		}



		case ADD: {
			rd_value_u_EX = rs1_value_u_EX + rs2_value_u_EX;
			break;
		}

		case SUB: {
			rd_value_u_EX = rs1_value_u_EX - rs2_value_u_EX;
			break;
		}

		case SLL: {
			rd_value_u_EX = rs1_value_u_EX << immediate_EX;
			break;
		}

		case SLT: {
			if ((int)rs1_value_u_EX < (int)rs2_value_u_EX) rd_value_u_EX = 1;
			else rd_value_u_EX = 0;
			break;
		}

		case SLTU: {
			if (rs1_value_u_EX < rs2_value_u_EX) rd_value_u_EX = 1;
			else rd_value_u_EX = 0;
			break;
		}

		case XOR: {
			rd_value_u_EX = rs1_value_u_EX ^ rs2_value_u_EX;
			break;
		}

		case SRL: {
			rd_value_u_EX = rs1_value_u_EX >> immediate_EX;
			break;
		}

		case SRA: {
			rd_value_u_EX = (int)rs1_value_u_EX << immediate_EX;
			break;
		}

		case OR: {
			rd_value_u_EX = rs1_value_u_EX | rs2_value_u_EX;
			break;
		}

		case AND: {
			rd_value_u_EX = rs1_value_u_EX & rs2_value_u_EX;
			break;
		}

		}

		/*testOutput_EX();*/
		EXConvertToMEM();
		flag_EX = false;
	}
}

void RISCV::MEM()
{
	if (flag_MEM) {

		MEMGetFromEX();

		switch (iType_MEM) {

		case BEQ: case BNE: case BLT: case BGE: case BLTU: case BGEU: {
			pc = pc_value_MEM;
			break;
		}

		case LB: {
			rd_value_u_MEM = 0;
			
			rd_value_u_MEM += HexToNumber(memory[2 * lsaddress_MEM + 1]);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM]) << 4);
			rd_value_u_MEM = (int)(rd_value_u_MEM << 24) >> 24;

			break;
		}

		case LH: {
			rd_value_u_MEM = 0;

			rd_value_u_MEM += HexToNumber(memory[2 * lsaddress_MEM + 1]);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM]) << 4);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM + 3]) << 8);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM + 2]) << 12);
			rd_value_u_MEM = (int)(rd_value_u_MEM << 16) >> 16;
			
			break;
		}

		case LW: {
			rd_value_u_MEM = 0;
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 2; ++j)
					rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM + 2 * i + j]) << (8 * i - 4 * j + 4));
	
			break;
		}

		case LBU: {
			rd_value_u_MEM = 0;

			rd_value_u_MEM += HexToNumber(memory[2 * lsaddress_MEM + 1]);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM]) << 4);

			break;
		}

		case LHU: {
			rd_value_u_MEM = 0;

			rd_value_u_MEM += HexToNumber(memory[2 * lsaddress_MEM + 1]);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM]) << 4);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM + 3]) << 8);
			rd_value_u_MEM += (HexToNumber(memory[2 * lsaddress_MEM + 2]) << 12);
			break;
		}

		case SB: {
			NumberToHex((x[rs2_MEM] & 15), memory[2 * lsaddress_MEM + 1]);
			NumberToHex(((x[rs2_MEM] >> 4) & 15), memory[2 * lsaddress_MEM]);

			break;
		}

		case SH: {	
			NumberToHex((x[rs2_MEM] & 15) , memory[2 * lsaddress_MEM + 1]);
			NumberToHex(((x[rs2_MEM] >> 4) & 15), memory[2 * lsaddress_MEM]);
			NumberToHex(((x[rs2_MEM] >> 8) & 15), memory[2 * lsaddress_MEM + 3]);
			NumberToHex(((x[rs2_MEM] >> 12) & 15), memory[2 * lsaddress_MEM + 2]);

			break;
		}

		case SW: {		
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 2; ++j)
					NumberToHex((x[rs2_MEM] >> (8 * i - 4 * j + 4)) & 15, memory[2 * lsaddress_MEM + 2 * i + j]);

			break;

		}
		}




		/*testOutput_MEM();*/
		MEMConvertToWB();
		flag_MEM = false;
	}
}

void RISCV::WB()
{
	if (flag_WB) {

		WBGetFromMEM();

		switch (iType_WB) {
		case END: endTag = true; break;

		case LUI: case AUIPC: case JAL: case JALR: case LB:case LH:case LW:
		case LBU:case LHU:case ADDI:case SLTI:case SLTIU:case XORI:case ORI:
		case ANDI:case ADD: case SUB: case SLL: case SLT: case SLTU: case XOR:
		case SRL: case SRA: case OR: case AND:
		{
				x[rd_WB] = rd_value_u_WB;
			break;
		}

		case SLLI:case SRLI:case SRAI: {
			if (shiftFlag_WB) {
					x[rd_WB] = rd_value_u_WB;
			}
			break;
		}

		}

		if (x[0] != 0) {
			x[0] = 0;
		}

		/*testOutput_WB();*/
		flag_WB = false;
	}
}


void RISCV::NumberToHex(int num, char& result)
{
	if (num <= 9) result = '0' + num;
	else result = 'A' + num - 10;
}

unsigned int RISCV::HexToNumber(char& num) {
	if (num <= '9') return (unsigned int)(num - '0');
	else return (unsigned int)(num - 'A' + 10);
}

void RISCV::testOutput_IF()
{
	switch (iType_IF) {
	case LUI: cout << "IF LUI "; break;
	case AUIPC: cout << "IF AUIPC "; break;
	case JAL:cout << "IF JAL "; break;
	case JALR: cout << "IF JALR "; break;
	case BEQ: cout << "IF BEQ "; break;
	case BNE: cout << "IF BNE "; break;
	case BLT: cout << "IF BLT "; break;
	case BGE: cout << "IF BGE "; break;
	case BLTU: cout << "IF BLTU "; break;
	case BGEU: cout << "IF BGEU "; break;
	case LB: cout << "IF LB "; break;
	case LH: cout << "IF LH "; break;
	case LW: cout << "IF LW "; break;
	case LBU: cout << "IF LBU "; break;
	case LHU: cout << "IF LHU "; break;
	case SB: cout << "IF SB "; break;
	case SH: cout << "IF SH "; break;
	case SW: cout << "IF SW "; break;
	case ADDI: cout << "IF ADDI "; break;
	case SLTI: cout << "IF SLTI "; break;
	case SLTIU: cout << "IF SLTIU "; break;
	case XORI: cout << "IF XORI "; break;
	case ORI: cout << "IF ORI "; break;
	case ANDI: cout << "IF ANDI "; break;
	case SLLI: cout << "IF SLLI "; break;
	case SRLI: cout << "IF SRLI "; break;
	case SRAI: cout << "IF SRAI "; break;
	case ADD: cout << "IF ADD "; break;
	case SUB: cout << "IF SUB "; break;
	case SLL: cout << "IF SLL "; break;
	case SLT: cout << "IF SLT "; break;
	case SLTU: cout << "IF SLTU "; break;
	case XOR: cout << "IF XOR "; break;
	case SRL: cout << "IF SRL "; break;
	case SRA: cout << "IF SRA "; break;
	case OR: cout << "IF OR "; break;
	case AND: cout << "IF AND "; break;
	case END: cout << "IF END "; break;
	}

	cout << pc << endl;
	for (int i = 0; i < 32; ++i)
		cout << x[i] << " ";
	cout << endl << endl;

}

void RISCV::testOutput_ID()
{
	switch (iType_ID) {
	case LUI: cout << "ID LUI "; break;
	case AUIPC: cout << "ID AUIPC "; break;
	case JAL:cout << "ID JAL "; break;
	case JALR: cout << "ID JALR "; break;
	case BEQ: cout << "ID BEQ "; break;
	case BNE: cout << "ID BNE "; break;
	case BLT: cout << "ID BLT "; break;
	case BGE: cout << "ID BGE "; break;
	case BLTU: cout << "ID BLTU "; break;
	case BGEU: cout << "ID BGEU "; break;
	case LB: cout << "ID LB "; break;
	case LH: cout << "ID LH "; break;
	case LW: cout << "ID LW "; break;
	case LBU: cout << "ID LBU "; break;
	case LHU: cout << "ID LHU "; break;
	case SB: cout << "ID SB "; break;
	case SH: cout << "ID SH "; break;
	case SW: cout << "ID SW "; break;
	case ADDI: cout << "ID ADDI "; break;
	case SLTI: cout << "ID SLTI "; break;
	case SLTIU: cout << "ID SLTIU "; break;
	case XORI: cout << "ID XORI "; break;
	case ORI: cout << "ID ORI "; break;
	case ANDI: cout << "ID ANDI "; break;
	case SLLI: cout << "ID SLLI "; break;
	case SRLI: cout << "ID SRLI "; break;
	case SRAI: cout << "ID SRAI "; break;
	case ADD: cout << "ID ADD "; break;
	case SUB: cout << "ID SUB "; break;
	case SLL: cout << "ID SLL "; break;
	case SLT: cout << "ID SLT "; break;
	case SLTU: cout << "ID SLTU "; break;
	case XOR: cout << "ID XOR "; break;
	case SRL: cout << "ID SRL "; break;
	case SRA: cout << "ID SRA "; break;
	case OR: cout << "ID OR "; break;
	case AND: cout << "ID AND "; break;
	case END: cout << "ID END "; break;
	}

	cout << pc << endl;
	for (int i = 0; i < 32; ++i)
		cout << x[i] << " ";
	cout << endl << endl;

}

void RISCV::testOutput_EX()
{
	switch (iType_EX) {
	case LUI: cout << "EX LUI "; break;
	case AUIPC: cout << "EX AUIPC "; break;
	case JAL:cout << "EX JAL "; break;
	case JALR: cout << "EX JALR "; break;
	case BEQ: cout << "EX BEQ jumpPredictor" << jumpPredictor << " "; break;
	case BNE: cout << "EX BNE jumpPredictor" << jumpPredictor << " "; break;
	case BLT: cout << "EX BLT jumpPredictor" << jumpPredictor << " "; break;
	case BGE: cout << "EX BGE jumpPredictor" << jumpPredictor << " "; break;
	case BLTU: cout << "EX BLTU jumpPredictor" << jumpPredictor << " "; break;
	case BGEU: cout << "EX BGEU jumpPredictor" << jumpPredictor << " "; break;
	case LB: cout << "EX LB "; break;
	case LH: cout << "EX LH "; break;
	case LW: cout << "EX LW "; break;
	case LBU: cout << "EX LBU "; break;
	case LHU: cout << "EX LHU "; break;
	case SB: cout << "EX SB "; break;
	case SH: cout << "EX SH "; break;
	case SW: cout << "EX SW "; break;
	case ADDI: cout << "EX ADDI "; break;
	case SLTI: cout << "EX SLTI "; break;
	case SLTIU: cout << "EX SLTIU "; break;
	case XORI: cout << "EX XORI "; break;
	case ORI: cout << "EX ORI "; break;
	case ANDI: cout << "EX ANDI "; break;
	case SLLI: cout << "EX SLLI "; break;
	case SRLI: cout << "EX SRLI "; break;
	case SRAI: cout << "EX SRAI "; break;
	case ADD: cout << "EX ADD "; break;
	case SUB: cout << "EX SUB "; break;
	case SLL: cout << "EX SLL "; break;
	case SLT: cout << "EX SLT "; break;
	case SLTU: cout << "EX SLTU "; break;
	case XOR: cout << "EX XOR "; break;
	case SRL: cout << "EX SRL "; break;
	case SRA: cout << "EX SRA "; break;
	case OR: cout << "EX OR "; break;
	case AND: cout << "EX AND "; break;
	case END: cout << "EX END "; break;
	}

	cout << pc << endl;
	for (int i = 0; i < 32; ++i)
		cout << x[i] << " ";
	cout << endl << endl;

}

void RISCV::testOutput_MEM()
{
	switch (iType_MEM) {
	case LUI: cout << "MEM LUI "; break;
	case AUIPC: cout << "MEM AUIPC "; break;
	case JAL:cout << "MEM JAL "; break;
	case JALR: cout << "MEM JALR "; break;
	case BEQ: cout << "MEM BEQ "; break;
	case BNE: cout << "MEM BNE "; break;
	case BLT: cout << "MEM BLT "; break;
	case BGE: cout << "MEM BGE "; break;
	case BLTU: cout << "MEM BLTU "; break;
	case BGEU: cout << "MEM BGEU "; break;
	case LB: cout << "MEM LB "; break;
	case LH: cout << "MEM LH "; break;
	case LW: cout << "MEM LW "; break;
	case LBU: cout << "MEM LBU "; break;
	case LHU: cout << "MEM LHU "; break;
	case SB: cout << "MEM SB "; break;
	case SH: cout << "MEM SH "; break;
	case SW: cout << "MEM SW "; break;
	case ADDI: cout << "MEM ADDI "; break;
	case SLTI: cout << "MEM SLTI "; break;
	case SLTIU: cout << "MEM SLTIU "; break;
	case XORI: cout << "MEM XORI "; break;
	case ORI: cout << "MEM ORI "; break;
	case ANDI: cout << "MEM ANDI "; break;
	case SLLI: cout << "MEM SLLI "; break;
	case SRLI: cout << "MEM SRLI "; break;
	case SRAI: cout << "MEM SRAI "; break;
	case ADD: cout << "MEM ADD "; break;
	case SUB: cout << "MEM SUB "; break;
	case SLL: cout << "MEM SLL "; break;
	case SLT: cout << "MEM SLT "; break;
	case SLTU: cout << "MEM SLTU "; break;
	case XOR: cout << "MEM XOR "; break;
	case SRL: cout << "MEM SRL "; break;
	case SRA: cout << "MEM SRA "; break;
	case OR: cout << "MEM OR "; break;
	case AND: cout << "MEM AND "; break;
	case END: cout << "MEM END "; break;
	}

	cout << pc << endl;
	for (int i = 0; i < 32; ++i)
		cout << x[i] << " ";
	cout << endl << endl;

}

void RISCV::testOutput_WB()
{
	switch (iType_WB) {
	case LUI: cout << "WB LUI "; break;
	case AUIPC: cout << "WB AUIPC "; break;
	case JAL:cout << "WB JAL "; break;
	case JALR: cout << "WB JALR "; break;
	case BEQ: cout << "WB BEQ "; break;
	case BNE: cout << "WB BNE "; break;
	case BLT: cout << "WB BLT "; break;
	case BGE: cout << "WB BGE "; break;
	case BLTU: cout << "WB BLTU "; break;
	case BGEU: cout << "WB BGEU "; break;
	case LB: cout << "WB LB "; break;
	case LH: cout << "WB LH "; break;
	case LW: cout << "WB LW "; break;
	case LBU: cout << "WB LBU "; break;
	case LHU: cout << "WB LHU "; break;
	case SB: cout << "WB SB "; break;
	case SH: cout << "WB SH "; break;
	case SW: cout << "WB SW "; break;
	case ADDI: cout << "WB ADDI "; break;
	case SLTI: cout << "WB SLTI "; break;
	case SLTIU: cout << "WB SLTIU "; break;
	case XORI: cout << "WB XORI "; break;
	case ORI: cout << "WB ORI "; break;
	case ANDI: cout << "WB ANDI "; break;
	case SLLI: cout << "WB SLLI "; break;
	case SRLI: cout << "WB SRLI "; break;
	case SRAI: cout << "WB SRAI "; break;
	case ADD: cout << "WB ADD "; break;
	case SUB: cout << "WB SUB "; break;
	case SLL: cout << "WB SLL "; break;
	case SLT: cout << "WB SLT "; break;
	case SLTU: cout << "WB SLTU "; break;
	case XOR: cout << "WB XOR "; break;
	case SRL: cout << "WB SRL "; break;
	case SRA: cout << "WB SRA "; break;
	case OR: cout << "WB OR "; break;
	case AND: cout << "WB AND "; break;
	case END: cout << "WB END "; break;
	}

	cout << pc << endl;
	for (int i = 0; i < 32; ++i)
		cout << x[i] << " ";
	cout << endl << endl;

}

int main()
{
	RISCV a;
	a.readFile();
	a.run();
}













