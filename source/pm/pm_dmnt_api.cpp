/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <switch.h>
#include <stratosphere.hpp>
#include <stratosphere/pm.hpp>

#include "pm_ams.h"

namespace sts::pm::dmnt {

    /* Debug Monitor API. */
    Result StartProcess(u64 process_id) {
        return pmdmntStartProcess(process_id);
    }

    Result GetProcessId(u64 *out_process_id, const ncm::TitleId title_id) {
        return pmdmntGetTitlePid(out_process_id, static_cast<u64>(title_id));
    }

    Result GetApplicationProcessId(u64 *out_process_id) {
        return pmdmntGetApplicationPid(out_process_id);
    }

    Result HookToCreateApplicationProcess(Handle *out_handle) {
        return pmdmntEnableDebugForApplication(out_handle);
    }

    Result AtmosphereGetProcessInfo(Handle *out_handle, ncm::TitleLocation *out_loc, u64 process_id) {
        *out_handle = INVALID_HANDLE;
        *out_loc = {};
        return pmdmntAtmosphereGetProcessInfo(out_handle, reinterpret_cast<u64 *>(&out_loc->title_id), &out_loc->storage_id, process_id);
    }

    Result AtmosphereGetCurrentLimitInfo(u64 *out_current_value, u64 *out_limit_value, ResourceLimitGroup group, LimitableResource resource) {
        *out_current_value = 0;
        *out_limit_value   = 0;
        return pmdmntAtmosphereGetCurrentLimitInfo(out_current_value, out_limit_value, group, resource);
    }

}
