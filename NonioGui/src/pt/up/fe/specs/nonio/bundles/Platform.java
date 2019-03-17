/**
 * Copyright 2019 SPeCS.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License. under the License.
 */

package pt.up.fe.specs.nonio.bundles;

import pt.up.fe.specs.util.providers.KeyStringProvider;

public enum Platform implements KeyStringProvider {
    HOST_INTEL("host-intel"),
    ORPSOC_MOR1KX("orpsoc-mor1kx"),
    ORPSOC_OR1200("orpsoc-or1200");

    private final String name;

    private Platform(String name) {
        this.name = name;
    }

    @Override
    public String getKey() {
        return name;
    }
}
