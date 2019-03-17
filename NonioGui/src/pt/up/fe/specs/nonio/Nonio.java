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

package pt.up.fe.specs.nonio;

import java.io.File;

import pt.up.fe.specs.git.GitRepos;
import pt.up.fe.specs.util.SpecsIo;
import pt.up.fe.specs.util.SpecsLogs;

/**
 * Utility classes related to Nonio.
 * 
 * @author JoaoBispo
 *
 */
public class Nonio {

    private static final String NONIO_REPO = "https://github.com/specs-feup/nonio.git";
    private static final String MAIN_ASPECT = "Larad.lara";
    private static final String LARA_FOLDERNAME = "lara";
    private static final String BUNDLES_FOLDERNAME = "bundles";
    private static final String BUNDLE_COMPILERS = "compilers";
    private static final String BUNDLE_ALGORITHMS = "algorithms";
    private static final String BUNDLE_PLATFORMS = "platforms";
    private static final String BUNDLE_LANGUAGES = "languages";
    private static final String SCRIPTS_FOLDERNAME = "includes/scripts";
    // private static final String TOOLS_FILENAMES = "resources/tools.xml";

    private final File nonioFolder;

    public Nonio() {
        this.nonioFolder = config();
    }

    /**
     * Preparations for execution of Nonio (e.g., pulling repository).
     */
    private File config() {
        // Download repo
        File nonioLocalRepo = new GitRepos().getFolder(NONIO_REPO);

        SpecsLogs.debug((() -> "Found Nonio in path " + SpecsIo.getCanonicalPath(nonioLocalRepo)));

        // Set environment variable
        System.setProperty("NONIO_HOME", SpecsIo.getCanonicalPath(nonioLocalRepo));

        return nonioLocalRepo;
    }

    public File getNonioFolder() {
        return nonioFolder;
    }

    public File getMainAspect() {
        return SpecsIo.existingFile(nonioFolder, MAIN_ASPECT);
    }

    public File getDseLaraFolder() {
        return SpecsIo.existingFolder(nonioFolder, LARA_FOLDERNAME);
    }

    public File getBundlesFolder() {
        return SpecsIo.existingFolder(nonioFolder, BUNDLES_FOLDERNAME);
    }

    public File getCompilersBundleFolder() {
        return SpecsIo.existingFolder(getBundlesFolder(), BUNDLE_COMPILERS);
    }

    public File getAlgorithmsBundleFolder() {
        return SpecsIo.existingFolder(getBundlesFolder(), BUNDLE_ALGORITHMS);
    }

    public File getPlatformsBundleFolder() {
        return SpecsIo.existingFolder(getBundlesFolder(), BUNDLE_PLATFORMS);
    }

    public File getLanguagesBundleFolder() {
        return SpecsIo.existingFolder(getBundlesFolder(), BUNDLE_LANGUAGES);
    }

    public File getIncludeScriptsFolder() {
        return SpecsIo.existingFolder(nonioFolder, SCRIPTS_FOLDERNAME);
    }

    // public File getToolsXml() {
    // return SpecsIo.existingFile(nonioFolder, TOOLS_FILENAMES);
    // }
}
