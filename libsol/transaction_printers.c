#include "instruction.h"
#include "sol/parser.h"
#include "sol/transaction_summary.h"
#include "transaction_printers.h"
#include "util.h"

const InstructionBrief create_stake_account_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccount),
    STAKE_IX_BRIEF(StakeInitialize),
};
#define is_create_stake_account(infos, infos_length)\
    instruction_infos_match_briefs(                 \
        infos,                                      \
        create_stake_account_brief,                 \
        infos_length                                \
    )

const InstructionBrief create_stake_account_with_seed_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccountWithSeed),
    STAKE_IX_BRIEF(StakeInitialize),
};
#define is_create_stake_account_with_seed(infos, infos_length)  \
    instruction_infos_match_briefs(                             \
        infos,                                                  \
        create_stake_account_with_seed_brief,                   \
        infos_length                                            \
    )

const InstructionBrief create_nonce_account_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccount),
    SYSTEM_IX_BRIEF(SystemInitializeNonceAccount),
};
#define is_create_nonce_account(infos, infos_length)    \
    instruction_infos_match_briefs(                     \
        infos,                                          \
        create_nonce_account_brief,                     \
        infos_length                                    \
    )

const InstructionBrief create_nonce_account_with_seed_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccountWithSeed),
    SYSTEM_IX_BRIEF(SystemInitializeNonceAccount),
};
#define is_create_nonce_account_with_seed(infos, infos_length)  \
    instruction_infos_match_briefs(                             \
        infos,                                                  \
        create_nonce_account_with_seed_brief,                   \
        infos_length                                            \
    )

const InstructionBrief create_vote_account_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccount),
    VOTE_IX_BRIEF(VoteInitialize),
};
#define is_create_vote_account(infos, infos_length) \
    instruction_infos_match_briefs(                 \
        infos,                                      \
        create_vote_account_brief,                  \
        infos_length                                \
    )

const InstructionBrief create_vote_account_with_seed_brief[] = {
    SYSTEM_IX_BRIEF(SystemCreateAccountWithSeed),
    VOTE_IX_BRIEF(VoteInitialize),
};
#define is_create_vote_account_with_seed(infos, infos_length)   \
    instruction_infos_match_briefs(                             \
        infos,                                                  \
        create_vote_account_with_seed_brief,                    \
        infos_length                                            \
    )

static int print_create_stake_account(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountInfo* ca_info = &infos[0].system.create_account;
    const StakeInitializeInfo* si_info = &infos[1].stake.initialize;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create stake acct", ca_info->to);

    BAIL_IF(print_system_create_account_info(NULL, ca_info, header));
    BAIL_IF(print_stake_initialize_info(NULL, si_info, header));

    return 0;
}

static int print_create_stake_account_with_seed(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountWithSeedInfo* cws_info = &infos[0].system.create_account_with_seed;
    const StakeInitializeInfo* si_info = &infos[1].stake.initialize;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create stake acct", cws_info->to);

    BAIL_IF(print_system_create_account_with_seed_info(NULL, cws_info, header));
    BAIL_IF(print_stake_initialize_info(NULL, si_info, header));

    return 0;
}

static int print_create_nonce_account(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountInfo* ca_info = &infos[0].system.create_account;
    const SystemInitializeNonceInfo* ni_info = &infos[1].system.initialize_nonce;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create nonce acct", ca_info->to);

    BAIL_IF(print_system_create_account_info(NULL, ca_info, header));
    BAIL_IF(print_system_initialize_nonce_info(NULL, ni_info, header));

    return 0;
}

static int print_create_nonce_account_with_seed(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountWithSeedInfo* ca_info = &infos[0].system.create_account_with_seed;
    const SystemInitializeNonceInfo* ni_info = &infos[1].system.initialize_nonce;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create nonce acct", ca_info->to);

    BAIL_IF(print_system_create_account_with_seed_info(NULL, ca_info, header));
    BAIL_IF(print_system_initialize_nonce_info(NULL, ni_info, header));

    return 0;
}

static int print_create_vote_account(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountInfo* ca_info = &infos[0].system.create_account;
    const VoteInitializeInfo* vi_info = &infos[1].vote.initialize;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create vote acct", ca_info->to);

    BAIL_IF(print_system_create_account_info(NULL, ca_info, header));
    BAIL_IF(print_vote_initialize_info(NULL, vi_info, header));

    return 0;
}

static int print_create_vote_account_with_seed(
    const MessageHeader* header,
    const InstructionInfo* infos,
    size_t infos_length
) {
    const SystemCreateAccountWithSeedInfo* ca_info = &infos[0].system.create_account_with_seed;
    const VoteInitializeInfo* vi_info = &infos[1].vote.initialize;

    SummaryItem* item = transaction_summary_primary_item();
    summary_item_set_pubkey(item, "Create vote acct", ca_info->to);

    BAIL_IF(print_system_create_account_with_seed_info(NULL, ca_info, header));
    BAIL_IF(print_vote_initialize_info(NULL, vi_info, header));

    return 0;
}

int print_transaction(const MessageHeader* header, const InstructionInfo* infos, size_t infos_length) {
    if (infos_length > 1) {
        InstructionBrief nonce_brief = SYSTEM_IX_BRIEF(SystemAdvanceNonceAccount);
        if (instruction_info_matches_brief(infos, &nonce_brief)) {
            print_system_nonced_transaction_sentinel(&infos->system, header);
            infos++;
            infos_length--;
        }
    }

    switch (infos_length) {
        case 1:
            switch (infos->kind) {
                case ProgramIdSystem:
                    return print_system_info(&infos->system, header);
                case ProgramIdStake:
                    return print_stake_info(&infos->stake, header);
                case ProgramIdVote:
                    return print_vote_info(&infos->vote, header);
                case ProgramIdUnknown:
                    break;
            }
            break;
        case 2: {
            if (is_create_stake_account(infos, infos_length)) {
                return print_create_stake_account(header, infos, infos_length);
            } else if (is_create_stake_account_with_seed(infos, infos_length)) {
                return print_create_stake_account_with_seed(header, infos, infos_length);
            } else if (is_create_nonce_account(infos, infos_length)) {
                return print_create_nonce_account(header, infos, infos_length);
            } else if (is_create_nonce_account_with_seed(infos, infos_length)) {
                return print_create_nonce_account_with_seed(header, infos, infos_length);
            } else if (is_create_vote_account(infos, infos_length)) {
                return print_create_vote_account(header, infos, infos_length);
            } else if (is_create_vote_account_with_seed(infos, infos_length)) {
                return print_create_vote_account_with_seed(header, infos, infos_length);
            }
        }
        default:
            break;
    }

    return 1;
}
