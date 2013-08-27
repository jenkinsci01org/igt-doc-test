#ifndef I915_PERF_H
#define I915_PERF_H

#include <linux/perf_event.h>

#define I915_SAMPLE_BUSY	0
#define I915_SAMPLE_WAIT	1
#define I915_SAMPLE_SEMA	2

#define I915_SAMPLE_RCS		0
#define I915_SAMPLE_VCS		1
#define I915_SAMPLE_BCS		2
#define I915_SAMPLE_VECS	3

#define __I915_PERF_COUNT(ring, id) ((ring) << 4 | (id))

#define I915_PERF_COUNT_RCS_BUSY __I915_PERF_COUNT(I915_SAMPLE_RCS, I915_SAMPLE_BUSY)
#define I915_PERF_COUNT_RCS_WAIT __I915_PERF_COUNT(I915_SAMPLE_RCS, I915_SAMPLE_WAIT)
#define I915_PERF_COUNT_RCS_SEMA __I915_PERF_COUNT(I915_SAMPLE_RCS, I915_SAMPLE_SEMA)

#define I915_PERF_COUNT_VCS_BUSY __I915_PERF_COUNT(I915_SAMPLE_VCS, I915_SAMPLE_BUSY)
#define I915_PERF_COUNT_VCS_WAIT __I915_PERF_COUNT(I915_SAMPLE_VCS, I915_SAMPLE_WAIT)
#define I915_PERF_COUNT_VCS_SEMA __I915_PERF_COUNT(I915_SAMPLE_VCS, I915_SAMPLE_SEMA)

#define I915_PERF_COUNT_BCS_BUSY __I915_PERF_COUNT(I915_SAMPLE_BCS, I915_SAMPLE_BUSY)
#define I915_PERF_COUNT_BCS_WAIT __I915_PERF_COUNT(I915_SAMPLE_BCS, I915_SAMPLE_WAIT)
#define I915_PERF_COUNT_BCS_SEMA __I915_PERF_COUNT(I915_SAMPLE_BCS, I915_SAMPLE_SEMA)

#define I915_PERF_COUNT_VECS_BUSY __I915_PERF_COUNT(I915_SAMPLE_VECS, I915_SAMPLE_BUSY)
#define I915_PERF_COUNT_VECS_WAIT __I915_PERF_COUNT(I915_SAMPLE_VECS, I915_SAMPLE_WAIT)
#define I915_PERF_COUNT_VECS_SEMA __I915_PERF_COUNT(I915_SAMPLE_VECS, I915_SAMPLE_SEMA)

#define I915_PERF_ACTUAL_FREQUENCY 32
#define I915_PERF_REQUESTED_FREQUENCY 33
#define I915_PERF_ENERGY 34
#define I915_PERF_INTERRUPTS 35

static inline int
perf_event_open(struct perf_event_attr *attr,
		pid_t pid,
		int cpu,
		int group_fd,
		unsigned long flags)
{
#ifndef __NR_perf_event_open
#if defined(__i386__)
#define __NR_perf_event_open 336
#elif defined(__x86_64__)
#define __NR_perf_event_open 298
#else
#define __NR_perf_event_open 0
#endif
#endif
    attr->size = sizeof(*attr);
    return syscall(__NR_perf_event_open, attr, pid, cpu, group_fd, flags);
}

uint64_t i915_type_id(void);

#endif /* I915_PERF_H */