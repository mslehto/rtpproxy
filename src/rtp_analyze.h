/*
 * Copyright (c) 2004-2006 Maxim Sobolev <sobomax@FreeBSD.org>
 * Copyright (c) 2006-2007 Sippy Software, Inc., http://www.sippysoft.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _RTP_ANALYZE_H_
#define _RTP_ANALYZE_H_

struct rtpp_log;

#define SSRC_FMT "0x%.8X"

struct rtpp_session_stat_jitter {
    uint64_t prev_rtime_ts;
    uint32_t prev_ts;
    double jval;
    double jmax;
    double jtotal;
    long long pcount;
#if 0
    long long ts_rcount;
    long long ts_jcount;
#endif
    long long ts_dcount;
    long long seq_rcount;
    struct rtpp_ringbuf *ts_dedup;
};

struct rtpp_session_stat_last {
    long long pcount;
    uint32_t min_seq;
    uint32_t max_seq;
    uint32_t seq_offset;
    uint32_t ssrc;
    uint32_t seen[4096];
    uint32_t duplicates;
    uint32_t base_ts;
    uint16_t seq;
    double base_rtime;
};

struct rtpp_session_stat {
    uint32_t ssrc_changes;
    uint32_t psent;
    uint32_t precvd;
    uint32_t duplicates;
    uint32_t desync_count;
    uint32_t seq_res_count;
    struct rtpp_session_stat_last last;
    struct rtpp_session_stat_jitter jitter;
};

enum update_rtpp_stats_rval {UPDATE_OK = 0, UPDATE_SSRC_CHG = 1, UPDATE_ERR = -1};

int rtpp_stats_init(struct rtpp_session_stat *);
void rtpp_stats_destroy(struct rtpp_session_stat *);
enum update_rtpp_stats_rval update_rtpp_stats(struct rtpp_log *,
  struct rtpp_session_stat *, rtp_hdr_t *, struct rtp_info *, double);
void update_rtpp_totals(struct rtpp_session_stat *, struct rtpp_session_stat *);

#endif
